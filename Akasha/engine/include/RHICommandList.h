#pragma once

#include "RHIDefines.h"
#include "CoreDefines.h"
#include "TaskGraph/TaskGraphCommon.h"

class FRHICommandListBase;
struct FRHICommandBase
{
	FRHICommandBase* m_Next = nullptr;
	virtual void ExecuteAndDestruct(FRHICommandListBase& CmdList) = 0;
};

class AKADLL_API FRHICommandListBase : public FNoncopyable
{
public:
	FRHICommandListBase();
	~FRHICommandListBase();
};