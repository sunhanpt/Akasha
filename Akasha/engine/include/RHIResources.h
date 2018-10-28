#include "TypeDefines.h"
#include "CoreDefines.h"
#include "ThreadSafeCounter.h"
#include <cassert>

class AKADLL_API ARHIResource
{
public:
	ARHIResource()
		: m_MarkedForDelete(0)
		, m_bCommitted(false)
	{
	}

	virtual ~ARHIResource()
	{
		assert(m_NumRefs.GetValue() == 0);
	}
private:
	AThreadSafeCounter	m_NumRefs;
	mutable	int32		m_MarkedForDelete;
	bool				m_bCommitted;
};
