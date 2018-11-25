#include "stdafx.h"
#include "GameClient.h"
#include "Engine.h"

const FTexture2DRHIRef& FRenderTarget::GetRenderTargetTexture() const
{
	return m_RenderTargetTextureRHI;
}

float FRenderTarget::GetDisplayGamma() const
{
	if (GEngine == nullptr)
	{
		return 2.2f;
	}
	else
	{
		return GEngine->m_DisplayGamma;
	}
}

