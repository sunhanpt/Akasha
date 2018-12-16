#include "stdafx.h"
#include "DynamicRHI.h"
#include "ModuleManager.h"
#include "D3D11RHIPrivate.h"


FDynamicRHI* PlatformCreateDynamicRHI()
{
	FDynamicRHI* DynamicRHI = nullptr;

	// 目前仅仅实现 D3D11-SM5

	ERHIFeatureLevel::Type RequestedFeatureLevel = ERHIFeatureLevel::SM5;

	// load the dynamic RHI Module.
	IDynamicRHIModule* DynamicRHIModule = nullptr;

	std::wstring StrName = TEXT("D3D11");
	DynamicRHIModule = (IDynamicRHIModule*)&(FModuleManager::Get().LoadModuleChecked<FD3D11DynamicRHIModule>(StrName));

	if (DynamicRHIModule)
	{
		DynamicRHI = DynamicRHIModule->CreateRHI(RequestedFeatureLevel);
	}

	return DynamicRHI;
}