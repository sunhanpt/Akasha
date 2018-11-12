#pragma once

#include "TypeDefines.h"

// Algin a value to the nearest higher mutiple of 'Alignment', which must be a power of two.
template <typename T>
inline constexpr T Align(const T Ptr, int32 Alignment)
{
	return (T)(((int64)Ptr + Alignment - 1) & ~(Alignment - 1) );
}