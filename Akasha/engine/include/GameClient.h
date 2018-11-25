#pragma once
#include "TypeDefines.h"
#include "CoreDefines.h"
#include "RHIResources.h"
#include "IntPoint.h"

class FViewport;
class FCanvas;
class UWorld;

class FRenderTarget
{
public:
	virtual ~FRenderTarget() {}

	virtual const FTexture2DRHIRef& GetRenderTargetTexture() const;
	virtual FIntPoint GetSizeXY() const = 0;
	virtual float GetDisplayGamma() const;								//return display gamma expected for rendering to this render target

protected:
	FTexture2DRHIRef m_RenderTargetTextureRHI;
};

/**
* An abstract interface to a viewport's client.
* The viewport's client processes input received by the viewport, and draws the viewport.
* 负责处理input和draw
*/
class FViewportClient
{
public:
	FViewportClient() {}
	virtual ~FViewportClient() {}

public:
	virtual void		Draw(FViewport* Viewport, FCanvas* Canvas) {}
	virtual UWorld*		GetWorld() const { return nullptr; }
};


class FCommonViewportClient : public FViewportClient
{
public:

};