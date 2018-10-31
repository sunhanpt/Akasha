#pragma once
#include "TypeDefines.h"


enum class EClearBinding
{
	ENoneBound,
	EColorBound,
	EDepthStencilBound
};

struct FClearValueBinding
{
	struct DSValue
	{
		float Depth;
		uint32 Stencil;
	};

	FClearValueBinding() 
		: ColorBinding(EClearBinding::ENoneBound)
	{
	}

	FClearValueBinding(float R, float G, float B, float A)
		: ColorBinding(EClearBinding::EColorBound)
	{
		Value.Color[0] = R;
		Value.Color[1] = G;
		Value.Color[2] = B;



		Value.Color[3] = A;
	}



	EClearBinding ColorBinding;
	
	union ClearValueType
	{
		float Color[4];
		DSValue DSValue;
	}Value;
};