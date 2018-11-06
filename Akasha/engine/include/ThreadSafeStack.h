#pragma once

#include "TypeDefines.h"
#include "CoreDefines.h"
#include "ScopeLock.h"
#include <cassert>
#include <stack>
#include "CriticalSection.h"

template<class T>
class FThreadSafeStack
{
public:
	FThreadSafeStack()
		:ThreadsCritical()
	{}

	~FThreadSafeStack() {}

	int32 Size()
	{
		AScopeLock Scope(&ThreadsCritical);
		return (int32)m_Stack.size();
	}

	bool IsEmpty()
	{
		AScopeLock Scope(&ThreadsCritical);
		return m_Stack.empty();
	}

	void Push(T value)
	{
		AScopeLock Scope(&ThreadsCritical);
		m_Stack.push(value);
	}

	void Pop()
	{
		AScopeLock Scope(&ThreadsCritical);
		m_Stack.pop();
	}

	T& Top()
	{
		AScopeLock Scope(&ThreadsCritical);
		return m_Stack.top();
	}

private:
	std::stack<T> m_Stack;
	ACriticalSection ThreadsCritical;
};