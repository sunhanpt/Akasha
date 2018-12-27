#pragma once
#include <vector>
#include <directx/D3D11.h>
#include "RHIResources.h"
#include "ShaderCore.h"

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

struct FD3D11ShaderResourceTable : public FBaseShaderResourceTable
{
	/** Mapping of bound Textures to their location in resource tables. */
	std::vector<uint32> TextureMap;

	friend bool operator==(const FD3D11ShaderResourceTable& A, FD3D11ShaderResourceTable& B)
	{
		const FBaseShaderResourceTable& BaseA = A;
		const FBaseShaderResourceTable& BaseB = B;
		bool bEqual = true;
		bEqual &= (BaseA == BaseB);
		bEqual &= (A.TextureMap.size() == B.TextureMap.size());
		if (!bEqual)
		{
			return false;
		}
		bEqual &= (memcmp(A.TextureMap.data(), B.TextureMap.data(), sizeof(uint32) * A.TextureMap.size()) == 0);
		return bEqual;
	}
};

