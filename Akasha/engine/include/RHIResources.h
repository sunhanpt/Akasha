#pragma once

#include "TypeDefines.h"
#include "CoreDefines.h"
#include "ThreadSafeCounter.h"
#include <cassert>
#include "ThreadSafeStack.h"
#include "Hash.h"

class AKADLL_API ARHIResource
{
public:
	ARHIResource(bool InbDoNotDeferDelte = false)
		: m_MarkedForDelete(0)
		, m_bDoNotDeferDelete(InbDoNotDeferDelte)
		, m_bCommitted(false)
	{
	}

	virtual ~ARHIResource()
	{
		assert(m_NumRefs.GetValue() == 0);
	}

	__forceinline uint32 AddRef() const 
	{
		int32 NewValue = m_NumRefs.Increment();
		assert(NewValue > 0);
		return uint32(NewValue);
	}

	__forceinline uint32 Release() const
	{
		int32 NewValue = m_NumRefs.Decrement;
		if (NewValue == 0)
		{
			if (!DeferDelete())
			{
				delete this;
			}
			else
			{
				if (_InterlockedCompareExchange(&m_MarkedForDelete, 1, 0) == 0) // 保证此resouce只被放到pending中一次。
				{
					s_PendingDeletes.Push(const_cast<ARHIResource*>(this));
				}
			}
		}

		assert(NewValue >= 0);
		return uint32(NewValue);
	}

	__forceinline uint32 GetRefCount() const
	{
		int32 CurrentValue = m_NumRefs.GetValue();
		assert(CurrentValue >= 0);
		return uint32(CurrentValue);
	}

	void DoNoDeferDelete()
	{
		assert(!m_MarkedForDelete); // 没被排队删除
		m_bDoNotDeferDelete = true;
	}

	void SetCommitted(bool bInCommitted)
	{
		// 应该在render线程调用
		m_bCommitted = bInCommitted;
	}

	bool IsCommitted() const
	{
		// 应该在render线程调用
		return m_bCommitted;
	}

	static void FlushPendingDeltes();

private:
	mutable AThreadSafeCounter	m_NumRefs;
	mutable	int32				m_MarkedForDelete;
	bool						m_bDoNotDeferDelete;
	bool						m_bCommitted;

	static AThreadSafeStack<ARHIResource*>	s_PendingDeletes;
	static ARHIResource*					s_CurrentlyDeleting;

	__forceinline bool DeferDelete() const
	{
		return !m_bDoNotDeferDelete; // TODO: Add other conditions.
	}
};


class ARHIShader : public ARHIResource
{
public:
	ARHIShader(bool InbDoNotDeferDelete = false) : ARHIResource(InbDoNotDeferDelete) {}

#if _DEBUG
	std::string m_ShaderName;
#endif

private:
	AHash m_Hash;
};


class ARHIVertexShader : public ARHIResource {};
class ARHIHullShader : public ARHIResource {};
class ARHIDomainShader : public ARHIResource {};
class ARHIPixelShader : public ARHIResource {};
class ARHIGeometryShader : public ARHIResource {};
class ARHIComputerShader : public ARHIResource {};