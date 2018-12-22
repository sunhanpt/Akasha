#pragma once
#include "RHIResources.h"
#include <memory>
#include "directx/D3D11.h"
#include "Utility.h"

class FD3D11SamplerState : public FRHISamplerState
{
public:
	ID3D11SamplerState* Resource = nullptr;
	virtual ~FD3D11SamplerState()
	{
		SAFE_RELEASE(Resource);
	}
};

class FD3D11RasterizerState : public FRHIRasterizerState
{
public:
	ID3D11RasterizerState* Resource = nullptr;
	virtual ~FD3D11RasterizerState()
	{
		SAFE_RELEASE(Resource);
	}
};

class FD3D11DepthStencilState : public FRHIDepthStencilState
{
public:
	ID3D11DepthStencilState* Resource = nullptr;

	/* Describes the read/write state of the separate depth and stencil components of the DSV. */
	FExclusiveDepthStencil AccessType;

	virtual ~FD3D11DepthStencilState()
	{
		SAFE_RELEASE(Resource);
	}
};

class FD3D11BlendState :public FRHIBlendState
{
public:
	ID3D11BlendState* Resource = nullptr;

	virtual ~FD3D11BlendState()
	{
		SAFE_RELEASE(Resource);
	}
};
