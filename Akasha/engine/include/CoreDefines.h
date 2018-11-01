#pragma once
#include <cassert>

#ifdef _DLL_EXPPORTS
#define AKADLL_API __declspec(dllexport)
#else
#define AKADLL_API __declspec(dllimport)
#endif


#define CORE_API AKADLL_API
#define FORCEINLINE __forceinline

#define check assert

enum { INDEX_NONE = -1 };

#define MS_ALIGN(n) __declspec(align(n))