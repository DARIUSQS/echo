#pragma once

#ifdef EC_PLATFORM_WINDOWS
    #ifdef EC_BUILD_DLL
        #define ECHO_API __declspec(dllexport)
    #else 
        #define ECHO_API __declspec(dllimport)
    #endif
#else
    #define ECHO_API 
#endif
