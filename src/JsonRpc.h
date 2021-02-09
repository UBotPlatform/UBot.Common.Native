#pragma once
#include <cppcoro/task.hpp>
#include <string>
#include <functional>
#include <optional>
#include <cstdint>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <chrono>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include "ResultBox.h"

namespace ubot
{
	struct JsonRpcError
	{
		int Code;
		std::string Message;
		std::optional<rapidjson::Document> Data;
	};
	struct JsonRpcResult
	{
		rapidjson::Document Result;
		std::optional<JsonRpcError> Error;
	};
	using TWriter = rapidjson::Writer<rapidjson::StringBuffer>;
	class JsonRpc
	{
	public:
		struct BackgroundTask {
			struct promise_type {
				BackgroundTask get_return_object() noexcept { return {}; }
				std::experimental::suspend_never initial_suspend() noexcept { return {}; }
				std::experimental::suspend_never final_suspend() noexcept { return {}; }
				void return_void() noexcept {}
				void unhandled_exception() noexcept {}
			};
		};
		void FeedData(const std::string& data)
		{
			rapidjson::Document document;
			document.Parse<rapidjson::kParseFullPrecisionFlag>(data.data(), data.size());
			FeedDocument(std::move(document));
		}
		BackgroundTask FeedDocument(rapidjson::Document document)
		{
			rapidjson::GenericStringBuffer<rapidjson::UTF8<> > result;
			TWriter writer(result);
			bool needResponse = false;
			if (document.HasParseError()) {
				needResponse = true;
				writer.StartObject();
				writer.Key("jsonrpc");
				writer.String("2.0");
				this->Error(writer, JsonRpcError{ -32700 ,"Parse error" , std::nullopt });
				writer.EndObject();
			}
			else
			{
				if (document.IsArray()) {
					writer.StartArray();
					for (auto& member : document.GetArray()) {
						needResponse |= co_await ProcessData(std::move(member), writer);
					}
					writer.EndArray();
				}
				else
				{
					needResponse |= co_await ProcessData(std::move(document), writer);
				}
			}
			if (needResponse) {
				writer.Flush();
				this->sender(std::string(result.GetString(), result.GetSize()));
			}
		}
		void SetSender(std::function<void(const std::string &data)> sender)
		{
			this->sender = sender;
		}
		void SetHandler(const std::string& name, std::function<cppcoro::task<>(rapidjson::Value&& params, TWriter& writer)> handler)
		{
			this->handler[name] = handler;
		}
		JsonRpcResult Call(const std::string &name, std::function<void(TWriter& writer)> paramsBuilder)
		{
			uint64_t curSeq = this->seq++;
			rapidjson::GenericStringBuffer<rapidjson::UTF8<> > requestText;
			TWriter writer(requestText);
			writer.StartObject();
			writer.Key("jsonrpc");
			writer.String("2.0");
			writer.Key("method");
			writer.String(name.data(), name.size());
			writer.Key("id");
			writer.Uint64(curSeq);
			writer.Key("params");
			paramsBuilder(writer);
			writer.EndObject();
			writer.Flush();

			ResultBox<rapidjson::Document> resultBox;
			{
				std::lock_guard<std::mutex> mutx(mtx);
				pending[curSeq] = &resultBox;
			}
			this->sender(std::string(requestText.GetString(), requestText.GetSize()));
			auto respond = resultBox.WaitForResult(std::chrono::seconds(10));
			if (!respond.has_value()) {
				std::lock_guard<std::mutex> mutx(mtx);
				auto resultBoxKV = pending.find(curSeq);
				if (resultBoxKV != pending.end())
				{
					pending.erase(resultBoxKV);
				}
			}
			if (!respond.has_value())
			{
				return JsonRpcResult{ rapidjson::Document(), JsonRpcError{ -32000, "RPC call timed out", std::nullopt } };
			}
			auto& value = respond.value();
			auto pError = value.FindMember("error");
			if (pError != value.MemberEnd())
			{
				auto oError = &pError->value;
				auto errorInfo = JsonRpcError{ -32000, "Unknown error", std::nullopt };

				auto pCode = oError->FindMember("code");
				if (pCode != oError->MemberEnd() && pCode->value.IsInt())
				{
					errorInfo.Code = pCode->value.GetInt();
				}

				auto pMessage = oError->FindMember("message");
				if (pMessage != oError->MemberEnd() && pMessage->value.IsString())
				{
					errorInfo.Message = std::string(pCode->value.GetString(), pCode->value.GetStringLength());
				}

				auto pData = oError->FindMember("data");
				if (pData != oError->MemberEnd() )
				{
					rapidjson::Document errorDataDoc;
					errorDataDoc.CopyFrom(pCode->value, errorDataDoc.GetAllocator(), true);
					errorInfo.Data = std::optional(std::move(errorDataDoc));
				}
				return JsonRpcResult{ rapidjson::Document(), std::optional(std::move(errorInfo)) };
			}
			auto pResult = value.FindMember("result");
			if (pResult == value.MemberEnd())
			{
				return JsonRpcResult{ rapidjson::Document(), JsonRpcError{ -32603, "Internal error", std::nullopt } };
			}
			rapidjson::Document resultDoc;
			resultDoc.CopyFrom(pResult->value, resultDoc.GetAllocator(), true);
			return JsonRpcResult{ std::move(resultDoc), std::nullopt };
		}
		static void StartResult(TWriter& writer);
		static void EndResult(TWriter& writer);
		static void Error(TWriter& writer, const JsonRpcError& error);
	private:
		std::function<void(const std::string& data)> sender;
		std::mutex mtx;
		std::atomic_uint64_t seq = 0;
		std::unordered_map<uint64_t, ResultBox<rapidjson::Document>*> pending;
		std::unordered_map<std::string, std::function<cppcoro::task<>(rapidjson::Value&& params, TWriter& writer)>> handler;
		cppcoro::task<bool> ProcessData(rapidjson::Value&& value, TWriter& writer)
		{
			if (!value.IsObject())
			{
				writer.StartObject();
				writer.Key("jsonrpc");
				writer.String("2.0");
				this->Error(writer, JsonRpcError{ -32600 ,"Invalid Request" , std::nullopt });
				writer.EndObject();
				co_return true;
			}
			auto pMethod = value.FindMember("method");
			auto pId = value.FindMember("id");
			auto oId = pId == value.MemberEnd()  ? nullptr : &pId->value;
			if (pMethod != value.MemberEnd())
			{
				bool isNotification = oId == nullptr;
				auto oMethod = &pMethod->value;
				auto pParams = value.FindMember("params");
				if (!oMethod->IsString() || pParams == value.MemberEnd())
				{
					if (isNotification)
					{
						co_return false;
					}
					writer.StartObject();
					writer.Key("jsonrpc");
					writer.String("2.0");
					writer.Key("id");
					oId->Accept(writer);
					this->Error(writer, JsonRpcError{ -32600 ,"Invalid Request" , std::nullopt });
					writer.EndObject();
					co_return true;
				}
				auto phandler = handler.find(std::string(oMethod->GetString(), oMethod->GetStringLength()));
				if (phandler == handler.end())
				{
					if (isNotification)
					{
						co_return false;
					}
					writer.StartObject();
					writer.Key("jsonrpc");
					writer.String("2.0");
					writer.Key("id");
					oId->Accept(writer);
					this->Error(writer, JsonRpcError{ -32601 ,"Method not found", std::nullopt });
					writer.EndObject();
					co_return true;
				}
				if (isNotification)
				{
					rapidjson::GenericStringBuffer<rapidjson::UTF8<> > tempResult;
					TWriter tempWriter(tempResult);
					tempWriter.StartObject();
					co_await phandler->second(std::move(pParams->value), tempWriter);
					tempWriter.EndObject();
					co_return false;
				}
				else
				{
					writer.StartObject();
					writer.Key("jsonrpc");
					writer.String("2.0");
					writer.Key("id");
					oId->Accept(writer);
					co_await phandler->second(std::move(pParams->value), writer);
					writer.EndObject();
					co_return true;
				}
			}
			else
			{
				if (oId == nullptr || !oId->IsUint64())
				{
					co_return false;
				}
				ResultBox<rapidjson::Document> *resultBox;
				auto id = oId->GetUint64();
				{
					std::lock_guard<std::mutex> mutx(mtx);
					auto resultBoxKV = pending.find(id);
					if (resultBoxKV == pending.end())
					{
						co_return false;
					}
					resultBox = resultBoxKV->second;
					pending.erase(resultBoxKV);
				}
				rapidjson::Document doc;
				doc.CopyFrom(value, doc.GetAllocator(), true);
				resultBox->SetResult(std::move(doc));
				co_return false;
			}
		}
	};
}