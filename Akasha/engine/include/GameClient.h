#pragma once
#include "TypeDefines.h"
#include "CoreDefines.h"

class FViewport;
class FCanvas;
class UWorld;
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

	// TODO: 完善FViewportClient
	virtual bool		InputKey(FViewport* Viewport) {}
};
