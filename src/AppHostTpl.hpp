#include <skyr/percent_encoding/percent_encode.hpp>
#include "UBotClientHost.h"
#include "AppHost.h"
#include "UNativeStrHelper.h"
#include "UBotAppContext.h"
#include "RpcTemplate/RpcTemplateImpl.hpp"
#include "RpcTemplate/RpcHelperMacroImpl.hpp"
using namespace ubot;
#define UBotPP_ApiCall_T(funcName, TResult, name, ...)\
	UBotPP_ImplementApiCallSync(UNativeStr_WithSuffix(ubotApp ## funcName), TResult, name, __VA_ARGS__);\
	UBotPP_ImplementApiCallAsync(UNativeStr_WithSuffix(ubotApp ## funcName ## Async), TResult, name, __VA_ARGS__)
#define UBotPP_HandlerSetter_T(funcName, TResult, name, ...)\
	UBotPP_ImplementSyncHandlerSetter(UNativeStr_WithSuffix(ubotAppSet ## funcName ## Handler), TResult, name, __VA_ARGS__);\
	UBotPP_ImplementAsyncHandlerSetter(UNativeStr_WithSuffix(ubotAppSet ## funcName ## AsyncHandler), TResult, name, __VA_ARGS__)
#include "AppApiDefiner.hpp"
#undef UBotPP_ApiCall_T
#undef UBotPP_HandlerSetter_T

void __stdcall UNativeStr_WithSuffix(ubotAppHost)(
    void* ctx,
    Encoding::ConstStr op,
    Encoding::ConstStr urlStr,
    Encoding::ConstStr id)
{
    auto context = static_cast<AppContext*>(ctx);
    HostUBotClient(EncodingImpl::TempFrom(op).get(), 
        EncodingImpl::TempFrom(urlStr).get(), 
        &context->rpc,
        [=](const skyr::url& managerUrl, JsonRpc& rpc) -> std::string {
            auto clientUrl = managerUrl;
            std::string clientTken;
            auto registered = cppcoro::sync_wait(rpc.Call("register_app", [&](TWriter& writer)
                {
                    writer.StartArray();
                    writer.String(EncodingImpl::TempFrom(id).get());
                    writer.EndArray();
                }, true));
            if (registered.Error.has_value())
            {
                return "";
            }
            clientUrl.set_pathname("/api/app");
            clientUrl.set_search("?id=" + skyr::percent_encode(std::string(EncodingImpl::TempFrom(id).get())) + "&token=" + registered.Result.GetString());
            return clientUrl.href();
        }, context->startup);
}