#pragma once

#include <list>
#include "RHIResources.h"

class FRenderResource
{
public:
	static std::list<FRenderResource*>& GetResourceList(); // get the resource link.

	FRenderResource()
		: m_FeatureLevel(ERHIFeatureLevel::Num)
		, m_bInitialized(false)
	{}

	FRenderResource(ERHIFeatureLevel::Type InFeatureLevel)
		: m_FeatureLevel(InFeatureLevel)
		, m_bInitialized(false)
	{}

	virtual ~FRenderResource();

	/**
	* Initializes the dynamic RHI resource and/or RHI render target used by this resource.
	* Called when the resource is initialized, or when reseting all RHI resources.
	* Resources that need to initialize after a D3D device reset must implement this function.
	* This is only called by the rendering thread.
	*/
	virtual void InitDynamicRHI() {}

	/**
	* Releases the dynamic RHI resource and/or RHI render target resources used by this resource.
	* Called when the resource is released, or when reseting all RHI resources.
	* Resources that need to release before a D3D device reset must implement this function.
	* This is only called by the rendering thread.
	*/
	virtual void ReleaseDynamicRHI() {}

	/**
	* Initializes the RHI resources used by this resource.
	* Called when entering the state where both the resource and the RHI have been initialized.
	* This is only called by the rendering thread.
	*/
	virtual void InitRHI() {}

	/**
	* Releases the RHI resources used by this resource.
	* Called when leaving the state where both the resource and the RHI have been initialized.
	* This is only called by the rendering thread.
	*/
	virtual void ReleaseRHI() {}

	/**
	* Initializes the resource.
	* This is only called by the rendering thread.
	*/
	virtual void InitResource();

	/**
	* Prepares the resource for deletion.
	* This is only called by the rendering thread.
	*/
	virtual void ReleaseResource();

	/**
	* If the resource's RHI resources have been initialized, then release and reinitialize it.  Otherwise, do nothing.
	* This is only called by the rendering thread.
	*/
	void UpdateRHI();

	virtual std::wstring GetFriendlyName() const { return _TEXT("undefined"); }

	FORCEINLINE bool IsInitialized() { return m_bInitialized; }

protected:
	ERHIFeatureLevel::Type GetFeatureLevel() const { return m_FeatureLevel == ERHIFeatureLevel::Num ? ERHIFeatureLevel::SM5 : m_FeatureLevel; }
	FORCEINLINE bool HasValidFeatureLevel() const { return m_FeatureLevel < ERHIFeatureLevel::Num; }

private:
	ERHIFeatureLevel::Type			m_FeatureLevel;
	std::list<FRenderResource*>::iterator		m_ResourceLink;
	bool							m_bInitialized;
};

///**
//* Sends a message to the rendering thread to initialize a resource.
//* This is called in the game thread.
//*/
//extern AKADLL_API void BeginInitResource(FRenderResource* Resource);
//
///**
//* Sends a message to the rendering thread to update a resource.
//* This is called in the game thread.
//*/
//extern AKADLL_API void BeginUpdateResourceRHI(FRenderResource* Resource);
//
///**
//* Sends a message to the rendering thread to release a resource.
//* This is called in the game thread.
//*/
//extern AKADLL_API void BeginReleaseResource(FRenderResource* Resource);
//
///**
//* Enables the batching of calls to BeginReleaseResource
//* This is called in the game thread.
//*/
//extern AKADLL_API void StartBatchedRelease();
//
///**
//* Disables the batching of calls to BeginReleaseResource
//* This is called in the game thread.
//*/
//extern AKADLL_API void EndBatchedRelease();
//
///**
//* Sends a message to the rendering thread to release a resource, and spins until the rendering thread has processed the message.
//* This is called in the game thread.
//*/
//extern AKADLL_API void ReleaseResourceAndFlush(FRenderResource* Resource);

