#include "TypeDefines.h"
#include "CoreDefines.h"
#include "ThreadSafeCounter.h"
#include <cassert>
#include "ThreadSafeStack.h"

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

	}

	__forceinline uint32 GetRefCount() const
	{

	}

	void DoNoDeferDelete()
	{

	}

	void SetCommitted(bool bInCommitted)
	{

	}

	bool IsCommitted() const
	{

	}

	static void FlushPendingDeltes();
	static bool ByPass();

private:
	mutable AThreadSafeCounter	m_NumRefs;
	mutable	int32				m_MarkedForDelete;
	bool						m_bDoNotDeferDelete;
	bool						m_bCommitted;

	static AThreadSafeStack<ARHIResource>	s_PendingDeletes;
	static ARHIResource*					s_CurrentlyDeleting;
};
