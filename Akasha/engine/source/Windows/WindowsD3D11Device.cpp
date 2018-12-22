#include "stdafx.h"
#include <delayimp.h>
#include "directx/dxgi1_2.h"
#include "D3D11RHIPrivate.h"
#include "TaskGraph/TaskGraphCommon.h"
#include "TaskGraph/ThreadCoreGlobals.h"

bool D3D11RHI_ShouldCreateWithD3DDebug()
{
	// Use a debug device if specified on the command line.
	return true;
}

bool D3D11RHI_ShouldAllowAsyncResourceCreation()
{
	return false;
}

FD3D11DynamicRHI::FD3D11DynamicRHI(D3D_FEATURE_LEVEL InFeatureLevel)
	: FeatureLevel(InFeatureLevel)
{

}

FD3D11DynamicRHI::~FD3D11DynamicRHI()
{

}

void FD3D11DynamicRHI::Init()
{
	InitD3DDevice();
}

void FD3D11DynamicRHI::ShutDown()
{
	check(IsInGameThread() && IsInRenderingThread());  // require that the render thread has been shut down

	CleanupD3DDevice();

}

void FD3D11DynamicRHI::InitD3DDevice()
{
	check(IsInGameThread());

	if (!Direct3DDevice)
	{
		FD3D11Device* pDevice = nullptr;
		FD3D11DeviceContext* pDeviceContext = nullptr;

		D3D_FEATURE_LEVEL ActualFeatureLevel = FeatureLevel;

		uint32 DeviceFlags = D3D11RHI_ShouldAllowAsyncResourceCreation() ? 0 : D3D11_CREATE_DEVICE_SINGLETHREADED;

		// Use a debug device if specified on the command line.
		const bool bWithD3DDebug = D3D11RHI_ShouldCreateWithD3DDebug();

		if (bWithD3DDebug)
		{
			DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		}

		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			DeviceFlags,
			&FeatureLevel,
			1,
			D3D11_SDK_VERSION,
			&pDevice,
			&ActualFeatureLevel,
			&pDeviceContext
		);

		if (SUCCEEDED(hr))
		{
			Direct3DDevice.reset(pDevice);
			Direct3DDeviceIMContext.reset(pDeviceContext);
			GIsRHIInitialized = true;
		}
		else
		{
			Direct3DDevice = nullptr;
			Direct3DDeviceIMContext = nullptr;
		}
	}
}

void FD3D11DynamicRHI::CleanupD3DDevice()
{
	if (GIsRHIInitialized)
	{
		check(Direct3DDevice);
		check(Direct3DDeviceIMContext);
		GIsRHIInitialized = false;

		// TODO: Çå¿Õ¸÷ÖÖcache.


		Direct3DDeviceIMContext = nullptr;
		Direct3DDevice = nullptr;
	}
}

///////////////////////////////////*device*///////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
void FD3D11DynamicRHIModule::StartupModule()
{

}

FDynamicRHI* FD3D11DynamicRHIModule::CreateRHI(ERHIFeatureLevel::Type RequestedFeatureLevel /* = ERHIFeatureLevel::Num */)
{
	//return new FD3D11DynamicRHI(D3D_FEATURE_LEVEL_11_1);
	return nullptr;
}

