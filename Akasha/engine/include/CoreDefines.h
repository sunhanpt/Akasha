#pragma once

#ifdef _DLL_EXPPORTS
#define AKADLL_API __declspec(dllexport)
#else
#define AKADLL_API __declspec(dllimport)
#endif
