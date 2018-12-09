#include "stdafx.h"
#include "ModuleManager.h"
#include "TaskGraph\WindowsCriticalSection.h"
#include "TaskGraph\ScopeLock.h"
#include "TaskGraph\TaskGraphCommon.h"

FModuleManager::~FModuleManager()
{
	ModulesMap.clear();
}

FModuleManager& FModuleManager::Get()
{
	static FModuleManager* ModulerManager = nullptr;

	if (ModulerManager == nullptr)
	{
		static FCriticalSection FModuleSingletonConstructor;
		FScopeLock Guard(&FModuleSingletonConstructor);
		if (ModulerManager == nullptr)
		{
			check(IsInGameThread());

			ModulerManager = new FModuleManager;
		}
	}

	return *ModulerManager;
}
