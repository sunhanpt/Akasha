#pragma once

#include "RenderResource.h"
#include "TaskGraph/RefCounting.h"

class FD3D11DynamicRHI;

/** Size of the default constant buffer. */
#define MAX_GLOBAL_CONSTANT_BUFFER_SIZE		4096

// !!! These offsets must match the cbuffer register definitions in Common.usf !!!
enum ED3D11ShaderOffsetBuffer
{
	/** Default constant buffer. */
	GLOBAL_CONSTANT_BUFFER_INDEX = 0,
	MAX_CONSTANT_BUFFER_SLOTS
};

/** Sizes of constant buffers defined in ED3D11ShaderOffsetBuffer. */
extern const uint32 GConstantBufferSizes[MAX_CONSTANT_BUFFER_SLOTS];

// D3D constant buffer
class FD3D11ConstantBuffer : public FRenderResource, public FRefCountedObject
{
	FD3D11ConstantBuffer(FD3D11DynamicRHI* InD3D11RHI, uint32 InSize, uint32 SubBuffers = 1);
	virtual ~FD3D11ConstantBuffer();

	virtual void InitDynamicRHI() override;
	virtual void ReleaseDynamicRHI() override;

	void UpdateConstant(const uint8* Data, uint16 Offset, uint16 InSize)
	{

	}

private:
	FD3D11DynamicRHI*	D3DRHI;
	uint32				MaxSize;
	uint8*				ShadowData;
	uint32				CurrentUpdateSize;
	uint32				TotalUpdateSize;
};