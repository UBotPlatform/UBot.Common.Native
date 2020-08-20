#include "JsonRpc.h"

void ubot::JsonRpc::StartResult(TWriter& writer)
{
	writer.Key("result");
}

void ubot::JsonRpc::EndResult(TWriter& writer)
{
}

void ubot::JsonRpc::Error(TWriter& writer, const JsonRpcError& error)
{
	writer.Key("error");
	writer.StartObject();
	writer.Key("code");
	writer.Int(error.Code);
	writer.Key("message");
	writer.String(error.Message.data(), error.Message.size());
	if (error.Data.has_value())
	{
		writer.Key("data");
		error.Data.value().Accept(writer);
	}
	writer.String(error.Message.data(), error.Message.size());
	writer.EndObject();
}
