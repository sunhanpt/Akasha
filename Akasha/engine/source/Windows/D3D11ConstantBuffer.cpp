#include "stdafx.h"
#include "D3D11ConstantBuffer.h"
#include "AlignmentTemplates.h"


const uint32 GConstantBufferSizes[MAX_CONSTANT_BUFFER_SLOTS] =
{
	// CBs must be a multiple of 16
	(uint32)Align(MAX_GLOBAL_CONSTANT_BUFFER_SIZE, 16),
};

FD3D11ConstantBuffer::FD3D11ConstantBuffer(FD3D11DynamicRHI* InD3D11RHI, uint32 InSize, uint32 SubBuffers /* = 1 */)
	: D3DRHI(InD3D11RHI)
	, MaxSize(InSize)
	, ShadowData(nullptr)
	, CurrentUpdateSize(0)
	, TotalUpdateSize(0)
{
	InitResource();
}

FD3D11ConstantBuffer::~FD3D11ConstantBuffer()
{
	ReleaseResource();
}

void FD3D11ConstantBuffer::InitDynamicRHI()
{
	uint32 tSize = Align(MaxSize, 16);
	ShadowData = new uint8[tSize];
	memset(ShadowData, 0, sizeof(uint8) * tSize);
}

void FD3D11ConstantBuffer::ReleaseDynamicRHI()
{
	if (ShadowData)
	{
		delete ShadowData;
	}
}