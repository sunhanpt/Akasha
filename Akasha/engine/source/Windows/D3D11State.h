#pragma once
#include "RHIResources.h"
#include <memory>
#include "directx/D3D11.h"

class FD3D11SamplerState : public FRHISamplerState
{
public:
	std::shared_ptr<ID3D11SamplerState> Resource;
};
