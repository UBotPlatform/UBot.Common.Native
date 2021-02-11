#pragma once
#include "../../EventResultType.h"
namespace ubot
{
    struct NormalEventRespond
    {
        using NativeType = EventResultType;
        using NativeTypeEx = void;
    };

    struct ReasonableEventRespond
    {
        using NativeType = EventResultType;
        using NativeTypeEx = void*;
    };
}