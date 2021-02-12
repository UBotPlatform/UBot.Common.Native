#pragma once
#include "../../EventResultType.h"
namespace ubot
{
    struct ReasonableEventResponder
    {
        using NativeType = EventResultType;
        using NativeTypeEx = void*;
    };
}