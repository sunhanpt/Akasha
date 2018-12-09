#pragma once

#include "ModuleInterface.h"
#include <map>
#include <memory>

class FModuleManager
{
public:
	
	~FModuleManager();

	static FModuleManager& Get();

private:
	FModuleManager() = default;
	std::map<std::wstring, std::unique_ptr<IModuleInterface>> ModulesMap;
};