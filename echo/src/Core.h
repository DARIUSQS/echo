#pragma once

#include <cassert>

#ifdef EC_PLATFORM_WINDOWS
    #ifdef EC_BUILD_DLL
        #define ECHO_API __declspec(dllexport)
    #else 
        #define ECHO_API __declspec(dllimport)
    #endif
#else
    #define ECHO_API 
#endif

#define BIT(x) (1 << x)
#define EC_ASSERT(x, ...) {if(!(x)) {EC_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(1);}}

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Echo
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}
