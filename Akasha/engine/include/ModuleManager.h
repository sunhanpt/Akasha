#pragma once

#include "ModuleInterface.h"
#include <map>
#include <memory>

class FModuleManager
{
public:
	
	~FModuleManager();

	static FModuleManager& Get();
	template<typename TModuleInterface>
	static TModuleInterface& LoadModuleChecked(const std::wstring& InModuleName)
	{
		TModuleInterface& ModuleInterface = FModuleManager::Get().LoadModuleCheckedCore<TModuleInterface>(InModuleName);
		return ModuleInterface;
	}

private:
	FModuleManager() = default;
	std::map<std::wstring, std::shared_ptr<IModuleInterface>> ModulesMap;

	template<typename TModuleInterface>
	TModuleInterface& LoadModuleCheckedCore(const std::wstring& InModuleName)
	{
		auto it = ModulesMap.find(InModuleName);
		if (it != ModulesMap.end())
			return (IModuleInterface&)*(it->second);
		else
		{
			IModuleInterface* ModuleInterface = new IModuleInterface;
			ModuleInterface->StartupModule();
			ModulesMap.insert(std::make_pair<std::wstring, IModuleInterface>(InModuleName, ModuleInterface));

			return (TModuleInterface&)(*ModuleInterface);
		}
	}
};