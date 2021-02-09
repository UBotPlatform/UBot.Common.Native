#include "AsyncResponsor.h"
#include "RpcTemplate.hpp"
using namespace ubot;
void __stdcall ubotAsyncReturnNormalEventResult(void* async, EventResultType type)
{
	AsyncReturn(async, [type] (TWriter& writer){
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        EnumArg<EventResultType>::Write(writer, type);
        writer.EndObject();
        JsonRpc::EndResult(writer);
	});
}