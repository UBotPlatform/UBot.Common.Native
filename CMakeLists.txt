cmake_minimum_required(VERSION 3.8)
if(VCPKG_TARGET_TRIPLET MATCHES "-windows-static$")
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

project(ubot-common DESCRIPTION "UBot Commom")
add_library(ubot-common SHARED)
target_sources(ubot-common PRIVATE
    "src/AppHostA.cpp"
    "src/AppHostTpl.hpp"
    "src/AppHostU8.cpp"
    "src/AppHostW.cpp"
    "src/DllMain.cpp"
    "src/Export.def"
    "src/JsonRpc.cpp"
    "src/JsonRpc.h"
    "src/ResultBox.h"
    "src/UBotClientHost.cpp"
    "src/UBotClientHost.h"
    "src/UNativeStrHelper.cpp"
    "src/UNativeStrHelper.h"
    "src/third-party/ctpl_stl.h"
    "src/UBotAppContext.h"
    "src/AppHostCommon.cpp"
    "src/StringBoxTpl.hpp"
    "src/StringBoxA.cpp"
    "src/StringBoxU8.cpp"
    "src/StringBoxW.cpp"
    "src/StringBoxCommon.cpp"
    "src/RpcTemplate.hpp"
    "src/RpcTemplate/TrivialValue.hpp"
    "src/RpcTemplate/IntArg.hpp"
    "src/RpcTemplate/EnumArg.hpp"
    "src/RpcTemplate/JsonRawArg.hpp"
    "src/RpcTemplate/StringArg.hpp"
    "src/RpcTemplate/BoolArg.hpp"
    "src/RpcTemplate/FlattedStringArrayArg.hpp"
    "src/RpcTemplate/NormalResultResponder.hpp"
    "src/RpcTemplate/EventRespond.hpp"
    "src/AsyncResponsorTpl.hpp"
    "src/AsyncResponsorA.cpp"
    "src/AsyncResponsorU8.cpp"
    "src/AsyncResponsorW.cpp"
    "src/AsyncResponsorCommon.cpp")
if(WIN32)
    target_sources(ubot-common PRIVATE "src/Export.def")
endif()
target_include_directories(ubot-common PUBLIC "include")

find_package(skyr-url CONFIG REQUIRED)
target_link_libraries(ubot-common PRIVATE skyr::skyr-url)

find_package(RapidJSON CONFIG REQUIRED)
target_include_directories(ubot-common PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

find_package(cppcoro CONFIG REQUIRED)
target_link_libraries(ubot-common PRIVATE cppcoro)

find_path(IXWEBSOCKET_INCLUDE_DIR ixwebsocket/IXWebSocket.h)
find_library(IXWEBSOCKET_LIBRARY ixwebsocket)
target_include_directories(ubot-common PRIVATE ${IXWEBSOCKET_INCLUDE_DIR})
target_link_libraries(ubot-common PRIVATE ${IXWEBSOCKET_LIBRARY})
find_package(ZLIB REQUIRED)
target_link_libraries(ubot-common PRIVATE ZLIB::ZLIB)
find_library(MBEDTLS_LIBRARY mbedtls)
find_library(MBEDX509_LIBRARY mbedx509)
find_library(MBEDCRYPTO_LIBRARY mbedcrypto)
set(MBEDTLS_LIBRARIES "${MBEDTLS_LIBRARY}" "${MBEDX509_LIBRARY}" "${MBEDCRYPTO_LIBRARY}")
target_link_libraries(ubot-common PRIVATE ${MBEDTLS_LIBRARIES})
if(WIN32)
    target_link_libraries(ubot-common PRIVATE wsock32 ws2_32 shlwapi Crypt32)
endif()
if(UNIX)
    find_package(Threads)
    target_link_libraries(ubot-common PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()

set_property(TARGET ubot-common PROPERTY CXX_STANDARD 20)
set_property(TARGET ubot-common PROPERTY CXX_STANDARD_REQUIRED ON)