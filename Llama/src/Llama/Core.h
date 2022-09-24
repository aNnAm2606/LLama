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

//BIT field , define bit x as 1 shifted by x-places, so if you have BIT(1)
//you'll have bit at position 1, 0 would be 0 and etc. Event can go to multiple categories
#define BIT(x) (1 << x)


