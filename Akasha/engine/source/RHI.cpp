#include "stdafx.h"
#include "RHIResources.h"

AThreadSafeStack<ARHIResource*>	ARHIResource::s_PendingDeletes;
ARHIResource* ARHIResource::s_CurrentlyDeleting = nullptr;


void ARHIResource::FlushPendingDeltes()
{
	//assert(IsInRenderingThread());

}