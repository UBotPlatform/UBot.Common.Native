#include "AsyncResponsor.h"
#include "RpcTemplate.hpp"
using namespace ubot;
void __stdcall ubotAsyncReturnNormalEventResult(void* async_0, void* async_1, EventResultType type)
{
	AsyncReturn(async_0, async_1, [type] (TWriter& writer){
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        EnumArg<EventResultType>::Write(writer, type);
        writer.EndObject();
        JsonRpc::EndResult(writer);
	});
}