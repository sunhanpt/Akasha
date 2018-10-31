#pragma once
#include "TypeDefines.h"
#include <intrin.h>
#include <cmath>

struct FMath
{
	static __forceinline float Loge(float Value) { return logf(Value); }

	static __forceinline float Log2(float Value)
	{
		static const float LogToLog2 = 1.f / Loge(2.f);
		return Loge(Value) * LogToLog2;
	}

	static __forceinline int32 TruncToInt(float F)
	{
		return _mm_cvtt_ss2si(_mm_set_ss(F)); // ssָ�����. _mm_set_ss�ǽ����ݴ��ڴ���ص��Ĵ�����_mm_cvtt_ss2siȡ����
		//return (int32)F;
	}


};