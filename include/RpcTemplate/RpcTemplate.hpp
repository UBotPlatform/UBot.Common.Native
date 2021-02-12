#pragma once
#include "Arg/IntArg.hpp"
#include "Arg/EnumArg.hpp"
#include "Arg/JsonRawArg.hpp"
#include "Arg/StringArg.hpp"
#include "Arg/BoolArg.hpp"
#include "Arg/FlattedStringArrayArg.hpp"
#include "Arg/VoidArg.hpp"
#include "Arg/NormalEventResultArg.hpp"
#include "Responder/NormalResultResponder.hpp"
#include "Responder/ReasonableEventResponder.hpp"
namespace ubot
{
    template <typename T>
    struct void_to_nullptr
    {
        using type = T;
    };
    template <>
    struct void_to_nullptr<void>
    {
        using type = typename std::nullptr_t;
    };
    template <typename T>
    using void_to_nullptr_t = typename void_to_nullptr<T>::type;



    template <typename T>
    struct get_native_type_ex
    {
    private:
        template <typename T0> static typename T0::NativeTypeEx __test(int) {}
        template <typename T0> static void __test(...) {}
    public:
        using type = decltype(__test<T>(0));
    };
    template <typename T>
    using get_native_type_ex_t = typename get_native_type_ex<T>::type;

    template <typename TResult>
    struct async_handler_type_impl
    {
        using type = void(__stdcall*)(void* ctx, void* user, typename TResult::NativeType result);
    };
    template<>
    struct async_handler_type_impl<VoidArg>
    {
        using type = void(__stdcall*)(void* ctx, void* user);
    };
    template <typename TResult>
    using async_handler_t = typename async_handler_type_impl<TResult>::type;
}