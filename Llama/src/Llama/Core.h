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

#ifdef LLAMA_DEBUG
#define LLAMA_ENABLE_ASSERTS
#endif

#ifdef LLAMA_ENABLE_ASSERTS
#define LLAMA_ASSERT(x, ...) { if(!(x)) { LLAMA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LLAMA_CORE_ASSERT(x, ...) { if(!(x)) { LLAMA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LLAMA_ASSERT(x, ...)
#define LLAMA_CORE_ASSERT(x, ...)
#endif

//BIT field , define bit x as 1 shifted by x-places, so if you have BIT(1)
//you'll have bit at position 1, 0 would be 0 and etc. Event can go to multiple categories
#define BIT(x) (1 << x)
//This binds "this" with thesingkeplaceholder into that function
#define LLAMA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


