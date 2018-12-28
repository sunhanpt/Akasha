#include "stdafx.h"
#include "D3D11RHIPrivate.h"
#include <vector>

FPixelShaderRHIRef FD3D11DynamicRHI::RHICreatePixelShader(const std::vector<uint8>& Code)
{
	return std::shared_ptr<FRHIPixelShader>();
}