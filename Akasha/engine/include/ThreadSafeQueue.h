#pragma once

#include "TypeDefines.h"
#include "CoreDefines.h"
#include "taskgraph\ScopeLock.h"
#include <cassert>
#include <queue>

template<class T>
class FThreadSafeQueue
{
public:
	FThreadSafeQueue() {}

	~FThreadSafeQueue() {}

	int32 Size()
	{
		AScopeLock(&ThreadsCritical);
		return (int32)m_Queue.size();
	}

	bool IsEmpty()
	{
		AScopeLock(&ThreadsCritical);
		return m_Queue.empty();
	}

	void Push(T& value)
	{
		AScopeLock(&ThreadsCritical);
		m_Queue.push(value);
	}

	void Pop()
	{
		AScopeLock(&ThreadsCritical);
		m_Queue.pop();
	}

	T& Front()
	{
		AScopeLock(&ThreadsCritical);
		return m_Queue.front();
	}

	const T& Front()
	{
		AScopeLock(&ThreadsCritical);
		return m_Queue.front();
	}

private:
	std::queue<T> m_Queue;
	FCriticalSection ThreadsCritical;
};