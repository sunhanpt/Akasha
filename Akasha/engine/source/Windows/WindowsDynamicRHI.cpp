#include "stdafx.h"
#include "DynamicRHI.h"

FDynamicRHI* PlatformCreateDynamicRHI()
{
	FDynamicRHI* DynamicRHI = nullptr;

	// Ŀǰ����ʵ�� D3D11-SM5

	ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::SM5;

	// load the dynamic RHI Module.
	IDynamicRHIModule* DynamicRHIModule = nullptr;

	// TODO: 
	return DynamicRHIModule;
}