#pragma once

#include "TypeDefines.h"
#include "CoreDefines.h"
#include "ScopeLock.h"
#include <cassert>
#include <stack>

template<class T>
class AThreadSafeStack
{
public:
	AThreadSafeStack() {}

	~AThreadSafeStack() {}

	int32 Size()
	{
		AScopeLock(&ThreadsCritical);
		return (int32)m_Stack.size();
	}

	bool IsEmpty()
	{
		AScopeLock(&ThreadsCritical);
		return m_Stack.empty();
	}

	void Push(T& value)
	{
		AScopeLock(&ThreadsCritical);
		m_Stack.push(value);
	}

	void Pop()
	{
		AScopeLock(&ThreadsCritical);
		m_Stack.pop();
	}

	T& Top()
	{
		AScopeLock(&ThreadsCritical);
		return m_Stack.top();
	}

	const T& Top()
	{
		AScopeLock(&ThreadsCritical);
		return m_Stack.top();
	}

private:
	std::stack<T> m_Stack;
	ACriticalSection ThreadsCritical;
};