#include "AsyncResponsor.h"
#include "RpcTemplate.hpp"
using namespace ubot;
void __stdcall UNativeStr_WithSuffix(ubotAsyncReturnReasonableEventResult)(void* async, EventResultType type, Encoding::ConstStr reason)
{
    AsyncReturn(async, [type, reason](TWriter& writer) {
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        EnumArg<EventResultType>::Write(writer, type);
        writer.Key("reason");
        StringArg::Write(writer, reason);
        writer.EndObject();
        JsonRpc::EndResult(writer);
    });
}