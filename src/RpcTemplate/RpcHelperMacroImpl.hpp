#pragma once
#include <RpcTemplate/RpcTemplate.hpp>
#include "RpcTemplateImpl.hpp"

#define UBotPP_CallFromNativeHelper(TResult, name, ...) \
    ubot::CallFromNative<BOOST_PP_TUPLE_REM_CTOR(UBotPP_Params((TResult), , UBotPP_ParamTupleToType, __VA_ARGS__))>\
            UBotPP_Params((context->rpc) (name), , UBotPP_ParamTupleToParamName, __VA_ARGS__)

#define UBotPP_ImplementApiCallSync(funcName, TResult, name, ...) \
    UBotPP_DefineApiCallSync(funcName, TResult, name, __VA_ARGS__)\
    {\
        auto context = static_cast<ubot::AppContext*>(ctx);\
        if constexpr (ubot::is_trivial_value_v<decltype(ubot::CallFromNative<TResult>(context->rpc, "dummy"))>)\
        {\
            auto data = UBotPP_CallFromNativeHelper(TResult, name, __VA_ARGS__); \
            return data.get(); \
        }\
        else\
        {\
            thread_local static auto data = UBotPP_CallFromNativeHelper(TResult, name, __VA_ARGS__); \
            return data.get(); \
        }\
    }

#define UBotPP_CallFromNativeAsyncHelper(TResult, name, ...) \
    ubot::CallFromNativeAsync<BOOST_PP_TUPLE_REM_CTOR(UBotPP_Params((TResult), , UBotPP_ParamTupleToType, __VA_ARGS__))>\
            UBotPP_Params((context->rpc) (name), (std::bind_front(handler, ctx, user)), UBotPP_ParamTupleToParamName, __VA_ARGS__)  

#define UBotPP_ImplementApiCallAsync(funcName, TResult, name, ...) \
    UBotPP_DefineApiCallAsync(funcName, TResult, name, __VA_ARGS__)\
    {\
        auto context = static_cast<ubot::AppContext*>(ctx);\
        UBotPP_CallFromNativeAsyncHelper(TResult, name, __VA_ARGS__);\
    }

#define UBotPP_ImplementSyncHandlerSetter(funcName, TResult, name, ...)\
    UBotPP_DefineSyncHandlerSetter(funcName, TResult, name, __VA_ARGS__)\
    {\
        auto context = static_cast<ubot::AppContext*>(ctx);\
        ubot::SetNativeHandler<BOOST_PP_TUPLE_REM_CTOR(UBotPP_Params((TResult), , UBotPP_ParamTupleToType, __VA_ARGS__))>\
            (context->rpc, name, std::bind_front(handler, ctx, user));\
    }

#define UBotPP_ImplementAsyncHandlerSetter(funcName, TResult, name, ...)\
    UBotPP_DefineAsyncHandlerSetter(funcName, TResult, name, __VA_ARGS__)\
    {\
        auto context = static_cast<ubot::AppContext*>(ctx);\
        ubot::SetNativeAsyncHandler<BOOST_PP_TUPLE_REM_CTOR(UBotPP_Params((TResult), , UBotPP_ParamTupleToType, __VA_ARGS__))>\
            (context->rpc, name, std::bind_front(handler, ctx, user));\
    }