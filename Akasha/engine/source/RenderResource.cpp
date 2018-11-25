#include "stdafx.h"
#include "RenderResource.h"
#include "TaskGraph/ThreadCoreGlobals.h"
#include "RHI.h"
#include "CoreGlobals.h"

std::list<FRenderResource*>& FRenderResource::GetResourceList()
{
	static std::list<FRenderResource*> FirstResourceLink;
	return FirstResourceLink;
}

void FRenderResource::InitResource()
{
	check(IsInRenderingThread());
	if (!m_bInitialized)
	{
		GetResourceList().push_front(this);
		m_ResourceLink = GetResourceList().begin();
		if (GIsRHIInitialized)
		{
			InitDynamicRHI();
			InitRHI();
		}

		m_bInitialized = true;
	}
}

void FRenderResource::ReleaseResource()
{
	if (!GIsCriticalError)
	{
		check(IsInRenderingThread());
		if (m_bInitialized)
		{
			if (GIsRHIInitialized)
			{
				ReleaseRHI();
				ReleaseDynamicRHI();
			}

			GetResourceList().erase(m_ResourceLink);
			m_bInitialized = false;
		}
	}
}

void FRenderResource::UpdateRHI()
{
	check(IsInRenderingThread());
	if (m_bInitialized && GIsRHIInitialized)
	{
		ReleaseRHI();
		ReleaseDynamicRHI();
		InitDynamicRHI();
		InitRHI();
	}
}

FRenderResource::~FRenderResource()
{
	if (m_bInitialized && !GIsCriticalError)
	{
		// Log
	}
}