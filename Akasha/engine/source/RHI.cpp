#include "stdafx.h"
#include "RHIResources.h"

FThreadSafeStack<FRHIResource*>	FRHIResource::s_PendingDeletes;
FRHIResource* FRHIResource::s_CurrentlyDeleting = nullptr;


void FRHIResource::FlushPendingDeltes()
{
	//assert(IsInRenderingThread());

}