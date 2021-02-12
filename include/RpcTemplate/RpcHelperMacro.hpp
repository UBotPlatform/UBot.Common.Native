#pragma once
#include "RpcTemplate.hpp"
#include <functional>
#include <boost/preprocessor.hpp>
#define UBotPP_ParamTupleToNativeParam(s, data, elem) typename BOOST_PP_TUPLE_ELEM(0, elem)::NativeType BOOST_PP_TUPLE_ELEM(1, elem)
#define UBotPP_ParamTupleToParamName(s, data, elem) BOOST_PP_TUPLE_ELEM(1, elem)
#define UBotPP_ParamTupleToType(s, data, elem) BOOST_PP_TUPLE_ELEM(0, elem)

#define UBotPP_Params(prefix, suffix, op, ...) \
        BOOST_PP_IIF(\
            BOOST_PP_IS_EMPTY(__VA_ARGS__),\
            BOOST_PP_SEQ_TO_TUPLE(prefix suffix),\
            BOOST_PP_SEQ_TO_TUPLE(\
                    prefix BOOST_PP_SEQ_TRANSFORM(op, 0, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) suffix\
            )\
        )

#define UBotPP_DefineApiCallSync(funcName, TResult, name, ...) \
    typename TResult::NativeType __stdcall funcName UBotPP_Params((void* ctx), , UBotPP_ParamTupleToNativeParam, __VA_ARGS__)

#define UBotPP_DefineApiCallAsync(funcName, TResult, name, ...) \
    void __stdcall funcName UBotPP_Params((void* ctx) (void* user), (ubot::async_handler_t<TResult> handler), UBotPP_ParamTupleToNativeParam, __VA_ARGS__)

#define UBotPP_SyncHandlerType(TResult, ...)\
    std::conditional_t<\
        std::is_void_v<ubot::get_native_type_ex_t<TResult>>,\
        typename TResult::NativeType(__stdcall*) UBotPP_Params((void* ctx) (void* user), , UBotPP_ParamTupleToNativeParam, __VA_ARGS__),\
        typename TResult::NativeType(__stdcall*) UBotPP_Params((void* ctx) (void* user), (ubot::void_to_nullptr_t<ubot::get_native_type_ex_t<TResult>> __respond), UBotPP_ParamTupleToNativeParam, __VA_ARGS__)\
    >

#define UBotPP_DefineSyncHandlerSetter(funcName, TResult, name, ...)\
    void __stdcall funcName(void* ctx, void* user, UBotPP_SyncHandlerType(TResult, __VA_ARGS__) handler)

#define UBotPP_DefineAsyncHandlerSetter(funcName, TResult, name, ...)\
    void __stdcall funcName(void* ctx, void* user, void (__stdcall* handler) UBotPP_Params((void* ctx) (void* user), (void* async), UBotPP_ParamTupleToNativeParam, __VA_ARGS__))
