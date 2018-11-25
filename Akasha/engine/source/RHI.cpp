#include "stdafx.h"
#include "RHIResources.h"

bool GIsRHIInitialized = false;

FThreadSafeStack<FRHIResource*>	FRHIResource::s_PendingDeletes;
FRHIResource* FRHIResource::s_CurrentlyDeleting = nullptr;


void FRHIResource::FlushPendingDeltes()
{
	//assert(IsInRenderingThread());

}