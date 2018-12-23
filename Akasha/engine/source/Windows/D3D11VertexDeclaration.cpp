#include "stdafx.h"
#include "D3D11RHIPrivate.h"
#include "D3D11Resources.h"
#include <map>

int FCompareDesc(const void* A, const void *B)
{
	const D3D11_INPUT_ELEMENT_DESC* PA = (const D3D11_INPUT_ELEMENT_DESC*)A;
	const D3D11_INPUT_ELEMENT_DESC* PB = (const D3D11_INPUT_ELEMENT_DESC*)B;
	bool IsLess = ((int32)PA->AlignedByteOffset + PA->InputSlot * MAX_uint16) < ((int32)PB->AlignedByteOffset + PB->InputSlot * MAX_uint16);
	if (IsLess)
		return -1;
	else
		return 1;
}

struct FD3D11VertexDeclarationKey
{
	FD3D11VertexElements VertexElements;

	uint32 Hash;

	uint16 StreamStrides[MaxVertexElementCount];

	explicit FD3D11VertexDeclarationKey(const FVertexDeclarationElementList& InElements)
	{
		uint16 UsedStreamMask = 0;
		memset(StreamStrides, 0, sizeof(StreamStrides));

		for (int32 ElementIndex = 0; ElementIndex < InElements.size(); ElementIndex++)
		{
			const FVertexElement& Element = InElements[ElementIndex];
			D3D11_INPUT_ELEMENT_DESC D3DElement = { 0 };
			D3DElement.InputSlot = Element.StreamIndex;
			D3DElement.AlignedByteOffset = Element.Offset;
			switch (Element.Type)
			{
			case VET_Float1:		D3DElement.Format = DXGI_FORMAT_R32_FLOAT; break;
			case VET_Float2:		D3DElement.Format = DXGI_FORMAT_R32G32_FLOAT; break;
			case VET_Float3:		D3DElement.Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
			case VET_Float4:		D3DElement.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
			case VET_PackedNormal:	D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
			case VET_UByte4:		D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UINT; break;
			case VET_UByte4N:		D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
			case  VET_Color:		D3DElement.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
			case VET_Short2:		D3DElement.Format = DXGI_FORMAT_R16G16_SINT; break;
			case VET_Short4:		D3DElement.Format = DXGI_FORMAT_R16G16B16A16_SINT; break;
			case VET_Short2N:		D3DElement.Format = DXGI_FORMAT_R16G16_SNORM; break;
			case VET_Half2:			D3DElement.Format = DXGI_FORMAT_R16G16_FLOAT; break;
			case VET_Half4:			D3DElement.Format = DXGI_FORMAT_R16G16B16A16_FLOAT; break;
			case VET_Short4N:		D3DElement.Format = DXGI_FORMAT_R16G16B16A16_SNORM; break;
			case VET_UShort2:		D3DElement.Format = DXGI_FORMAT_R16G16_UINT; break;
			case VET_UShort4:		D3DElement.Format = DXGI_FORMAT_R16G16B16A16_UINT; break;
			case VET_UShort2N:		D3DElement.Format = DXGI_FORMAT_R16G16_UNORM; break;
			case  VET_UShort4N:		D3DElement.Format = DXGI_FORMAT_R16G16B16A16_UNORM; break;
			case VET_URGB10A2N:		D3DElement.Format = DXGI_FORMAT_R10G10B10A2_UNORM; break;
			default:
				break;
			}

			D3DElement.SemanticName = "ATTRIBUTE"; // 可以自定义语义名称
			D3DElement.SemanticIndex = Element.AttributeIndex;
			D3DElement.InputSlotClass = Element.bUseInstanceIndex ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;

			// This is a divisor to apply to the instance index used to read from this stream.
			D3DElement.InstanceDataStepRate = Element.bUseInstanceIndex ? 1 : 0;

			if ((UsedStreamMask & 1 << Element.StreamIndex) != 0)
			{
				check(StreamStrides[Element.StreamIndex] == Element.Stride);
			}
			else
			{
				UsedStreamMask = UsedStreamMask | (1 << Element.StreamIndex);
				StreamStrides[Element.StreamIndex] = Element.Stride;
			}

			VertexElements.push_back(D3DElement);
		}

		// Sort by stream then offset.
		//qsort(VertexElements.data(), VertexElements.size(), sizeof(D3D11_INPUT_ELEMENT_DESC), FCompareDesc);
		Hash = FCrc::MemCrc(VertexElements.data(), (int32)(sizeof(D3D11_INPUT_ELEMENT_DESC) * VertexElements.size()));
	}
};

/** Compare two vertex declaration keys. */
bool operator<(const FD3D11VertexDeclarationKey& A, const FD3D11VertexDeclarationKey& B)
{
	return A.Hash < B.Hash;
}


std::map<FD3D11VertexDeclarationKey, FVertexDeclarationRHIRef> GVertexDeclarationCache;

FVertexDeclarationRHIRef FD3D11DynamicRHI::RHICreateVertexDeclaration(const FVertexDeclarationElementList& Elements)
{
	FD3D11VertexDeclarationKey Key(Elements);

	auto Itor = GVertexDeclarationCache.find(Key);
	if (Itor == GVertexDeclarationCache.end())
	{
		auto& VertexDecl = std::make_shared<FD3D11VertexDeclaration>(Key.VertexElements, Key.StreamStrides);
		GVertexDeclarationCache[Key] = VertexDecl;
		return VertexDecl;
	}
	else
	{
		return Itor->second;
	}
}