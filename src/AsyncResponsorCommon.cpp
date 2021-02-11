#include "AsyncResponsor.h"
#include "RpcTemplate/RpcTemplateImpl.hpp"
using namespace ubot;
void __stdcall ubotAsyncReturnNormalEventResult(void* async, EventResultType type)
{
	AsyncReturn(async, [type] (TWriter& writer){
        JsonRpc::StartResult(writer);
        writer.StartObject();
        writer.Key("type");
        ArgImpl<EnumArg<EventResultType>>::Write(writer, type);
        writer.EndObject();
        JsonRpc::EndResult(writer);
	});
}