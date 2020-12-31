#pragma once
#include <functional>
#include "JsonRpc.h"
namespace ubot {
    struct AppContext {
        ubot::JsonRpc rpc;
        std::function<void()> startup;
    };
}