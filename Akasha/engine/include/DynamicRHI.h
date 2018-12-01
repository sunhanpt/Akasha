#pragma once

#include "RHIResources.h"

// �൱��d3d�е�device
class FDynamicRHI
{
public:
	virtual ~FDynamicRHI() {}

	virtual void Init() = 0;

	virtual void PostInit() {}

	virtual void ShutDown() = 0;

	virtual const TCHAR* GetName() = 0;

	virtual FSamplerStateRHIParamRef RHICreateSamplerState(const FSamplerStateInitializerRHI& Initializer) = 0;

	virtual FRasterizerStateRHIRef RHICreateRaterizeState(const FRaterizerStateInitializerRHI& Initializer) = 0;

	//virtual FDepthStencilStateRHIRef RHICrateDepthStencilState(const ) = 0;
};