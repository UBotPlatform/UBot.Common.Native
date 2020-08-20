#include "UBotClientHost.h"
namespace ubot 
{
    std::unique_ptr<ix::WebSocket> DialRouter(
        const char* op,
        const char* urlStr,
        ix::OnMessageCallback onMessageCallback,
        std::function<std::string(const skyr::url& managerUrl, ubot::JsonRpc& rpc)> registerClient)
    {
        std::string clientUrlStr;
        if (_strcmpi(op, "applyto") == 0)
        {
            auto managerUrl = skyr::url(std::string(urlStr));
            if (managerUrl.username().length() || managerUrl.password().length())
            {
                auto user = managerUrl.username(), password = managerUrl.password();
                managerUrl.set_username("");
                managerUrl.set_password("");

                auto getTokenUrl = managerUrl;
                getTokenUrl.set_protocol(getTokenUrl.protocol() == std::string("wss") ? std::string("https") : std::string("http"));
                getTokenUrl.set_pathname("/api/manager/get_token");
                auto getTokenUrlStr = getTokenUrl.href();

                std::cout << "Getting manager token from " << getTokenUrlStr << std::endl;
                ix::HttpClient httpClient;
                auto getTokenArgs = httpClient.createRequest(getTokenUrlStr);
                auto managerToken = httpClient.post(getTokenUrlStr,
                    "user=" + skyr::percent_encode<std::string>(user) + "&password=" + skyr::percent_encode<std::string>(password),
                    getTokenArgs)->payload;
                if (managerToken.length() == 0)
                {
                    std::cout << "Failed to get the manager token" << std::endl;
                    return nullptr;
                }
                std::cout << "Got manager token" << std::endl;

                managerUrl.set_search("?token=" + managerToken);
            }
            auto managerUrlStr = managerUrl.href();
            std::cout << "Applying to " << managerUrlStr << std::endl;
            ubot::ResultBox<bool> connectResult;
            ix::WebSocket managerConn;
            ubot::JsonRpc managerRpc;
            managerConn.disableAutomaticReconnection();
            managerConn.setUrl(managerUrlStr);
            managerRpc.SetSender([&](const std::string& data)
                {
                    managerConn.sendText(data);
                });
            managerConn.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
                {
                    switch (msg->type)
                    {
                    case ix::WebSocketMessageType::Message:
                        managerRpc.FeedData(msg->str);
                        break;
                    case ix::WebSocketMessageType::Open:
                        connectResult.SetResult(true);
                        break;
                    case ix::WebSocketMessageType::Error:
                        break;
                    }
                }
            );
            managerConn.start();
            connectResult.WaitForResult(std::chrono::seconds(5));
            clientUrlStr = registerClient(managerUrl, managerRpc);
            managerConn.stop();
            if (clientUrlStr.length() == 0)
            {
                std::cout << "Failed to register the client" << std::endl;
                return nullptr;
            }
            std::cout << "Applied" << std::endl;
        }
        else if (_strcmpi(op, "connect") == 0)
        {
            clientUrlStr = urlStr;
        }
        else
        {
            return nullptr;
        }
        std::cout << "Connecting to " << clientUrlStr << std::endl;
        auto conn = std::make_unique<ix::WebSocket>();
        conn->disableAutomaticReconnection();
        conn->setUrl(clientUrlStr);
        conn->setOnMessageCallback(onMessageCallback);
        if (!conn->connect(5000).success)
        {
            std::cout << "Failed to dial to router" << std::endl;
            return nullptr;
        }
        std::cout << "Connected" << std::endl;
        return conn;
    }

    void HostUBotClient(
        const char* op,
        const char* urlStr,
        std::function<std::string(const skyr::url& managerUrl, ubot::JsonRpc& rpc)> registerClient,
        std::function<void(ubot::JsonRpc& rpc)> configRPC,
        std::function<void()> startup)
    {
        ix::initNetSystem();
        ctpl::thread_pool taskPool(4);
        std::unique_ptr<ix::WebSocket> ws;
        ubot::JsonRpc rpc;
        auto onMessageCallback = [&](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                auto msgContent = msg->str;
                taskPool.push([&rpc, msgContent = std::move(msgContent)](int)
                {
                    rpc.FeedData(msgContent);
                });
            }
        };
        for (int retryCount = 0; retryCount < 5; retryCount++)
        {
            ws = DialRouter(op, urlStr, onMessageCallback, registerClient);
            if (ws != nullptr)
            {
                break;
            }
            std::cout << "Failed to connect to UBot Router, it will try again in 5 seconds." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        if (ws == nullptr)
        {
            std::cout << "Failed to connect to UBot Router after 5 attempts." << std::endl;
            return;
        }
        rpc.SetSender([&](const std::string& data)
            {
                ws->sendText(data);
            });
        configRPC(rpc);
        taskPool.push([startup](int)
            {
                startup();
            });
        ws->run();
    }
}