#pragma once
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXHttpClient.h>
#include <iostream>
#include <memory>
#include <skyr/url.hpp>
#include <skyr/percent_encoding/percent_encode.hpp>
#include "JsonRpc.h"
#include <thread>
#include "third-party/ctpl_stl.h"
namespace ubot
{
    std::unique_ptr<ix::WebSocket> DialRouter(
        const char* op,
        const char* urlStr,
        ix::OnMessageCallback onMessageCallback,
        std::function<std::string(const skyr::url& managerUrl, ubot::JsonRpc& rpc)> registerClient);
    void HostUBotClient(
        const char* op,
        const char* urlStr,
        std::function<std::string(const skyr::url& managerUrl, ubot::JsonRpc& rpc)> registerClient,
        std::function<void(ubot::JsonRpc& rpc)> configRPC,
        std::function<void()> startup);
}