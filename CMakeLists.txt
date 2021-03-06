﻿cmake_minimum_required(VERSION 3.8)
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
    "src/UBotAppContext.h"
    "src/AppHostCommon.cpp"
    "src/StringBoxTpl.hpp"
    "src/StringBoxA.cpp"
    "src/StringBoxU8.cpp"
    "src/StringBoxW.cpp"
    "src/StringBoxCommon.cpp"
    "src/RpcTemplate/RpcTemplateImpl.hpp"
    "src/RpcTemplate/TrivialValue.hpp"
    "src/RpcTemplate/Arg/ArgImpl.hpp"
    "src/RpcTemplate/Arg/IntArgImpl.hpp"
    "src/RpcTemplate/Arg/EnumArgImpl.hpp"
    "src/RpcTemplate/Arg/JsonRawArgImpl.hpp"
    "src/RpcTemplate/Arg/StringArgImpl.hpp"
    "src/RpcTemplate/Arg/BoolArgImpl.hpp"
    "src/RpcTemplate/Arg/FlattedStringArrayArgImpl.hpp"
    "src/RpcTemplate/Arg/VoidArgImpl.hpp"
    "src/RpcTemplate/Arg/NormalEventResultArgImpl.hpp"
    "src/RpcTemplate/Responder/ResponderImpl.hpp"
    "src/RpcTemplate/Responder/NormalResultResponderImpl.hpp"
    "src/RpcTemplate/Responder/ReasonableEventResponderImpl.hpp"
    "src/AsyncResponsorTpl.hpp"
    "src/AsyncResponsorA.cpp"
    "src/AsyncResponsorU8.cpp"
    "src/AsyncResponsorW.cpp"
    "src/AsyncResponsorCommon.cpp"
    "src/unordered_string_map.hpp"
    "src/RpcTemplate/RpcHelperMacroImpl.hpp"
    "include/RpcTemplate/RpcHelperMacro.hpp"
    "include/RpcTemplate/ApiDefiner.hpp"
    "include/AppApiDefiner.hpp")
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

find_path(BOOST_PREPROCESSOR_INCLUDE_DIRS "boost/preprocessor.hpp")
target_include_directories(ubot-common PUBLIC ${BOOST_PREPROCESSOR_INCLUDE_DIRS})

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