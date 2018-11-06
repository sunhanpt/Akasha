#pragma once
#include "CoreDefines.h"
#include "TypeDefines.h"
#include <intrin.h>

class FThreadSafeCounter
{
public:
	FThreadSafeCounter()
	{
		m_Counter = 0;
	}

	FThreadSafeCounter(const FThreadSafeCounter& Other)
	{
		//m_Counter = 
	}

	FThreadSafeCounter(int32 Value)
	{
		m_Counter = Value;
	}

	int32 Increment()
	{
		return _InterlockedIncrement(&m_Counter);
	}

	int32 Add(int32 Amount)
	{
		return _InterlockedExchangeAdd(&m_Counter, Amount);
	}

	int32 Decrement()
	{
		return _InterlockedDecrement(&m_Counter);
	}

	int32 Subtract(int32 Amount)
	{
		return _InterlockedExchangeAdd(&m_Counter, -Amount);
	}

	int32 Set(int32 Value)
	{
		return _InterlockedExchange(&m_Counter, Value);
	}

	int32 ReSet(int32 Value)
	{
		return _InterlockedExchange(&m_Counter, 0);
	}

	int32 GetValue() const
	{
		return _InterlockedCompareExchange(&const_cast<FThreadSafeCounter*>(this)->m_Counter, 0, 0);
	}

private:
	// 此函数不安全所以隐藏掉
	void operator=(const FThreadSafeCounter& Other) {}
	volatile int32 m_Counter;
};