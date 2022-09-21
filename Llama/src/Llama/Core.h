#pragma once

#ifdef LLAMA_PLATFORM_WINDOWS
   #ifdef LLAMA_BUILD_DLL
       #define LLAMA_API __declspec(dllexport)

   #else 
       #define LLAMA_API __declspec(dllimport)
   #endif
#else
    #error Llama doesnt support this platform!
#endif


