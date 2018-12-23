#pragma once
#include <vector>
#include <directx/D3D11.h>
#include "RHIResources.h"

typedef std::vector<D3D11_INPUT_ELEMENT_DESC> FD3D11VertexElements;

class FD3D11VertexDeclaration : public FRHIVertexDeclaration
{
public:
	FD3D11VertexElements VertexElements = FD3D11VertexElements(MaxVertexElementCount);

	uint16 StreamStrides[MaxVertexElementCount];

	explicit FD3D11VertexDeclaration(const FD3D11VertexElements& InElements, const uint16* InStrides)
		: VertexElements(InElements)
	{
		memcpy(StreamStrides, InStrides, sizeof(StreamStrides));
	}
};