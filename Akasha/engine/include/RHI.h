#pragma once
#include "TypeDefines.h"
#include "Color.h"

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

	FLinearColor GetClearColor() const
	{
		assert(ColorBinding == EClearBinding::EColorBound);
		return FLinearColor(Value.Color[0], Value.Color[1], Value.Color[2], Value.Color[3]);
	}

	void GetDepthStencil(float& OutDepth, uint32& OutStencil) const
	{
		assert(ColorBinding == EClearBinding::EDepthStencilBound);
		OutDepth = Value.DSValue.Depth;
		OutStencil = Value.DSValue.Stencil;
	}

	bool operator==(const FClearValueBinding& Other) const
	{
		if (ColorBinding == Other.ColorBinding)
		{
			if (ColorBinding == EClearBinding::EColorBound)
			{
				return
					Value.Color[0] == Other.Value.Color[0] &&
					Value.Color[1] == Other.Value.Color[1] &&
					Value.Color[2] == Other.Value.Color[2] &&
					Value.Color[3] == Other.Value.Color[3];

			}
			if (ColorBinding == EClearBinding::EDepthStencilBound)
			{
				return
					Value.DSValue.Depth == Other.Value.DSValue.Depth &&
					Value.DSValue.Stencil == Other.Value.DSValue.Stencil;
			}
			return true;
		}
		return false;
	}

	EClearBinding ColorBinding;
	
	union ClearValueType
	{
		float Color[4];
		DSValue DSValue;
	}Value;
};