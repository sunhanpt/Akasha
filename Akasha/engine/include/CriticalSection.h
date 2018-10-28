#pragma once
/************************************************************************/
/* Critical Seciton
*  pengtong.pt 2018-10-28
*/
/************************************************************************/
#include <windows.h>

class ACriticalSection
{
public:
	__forceinline ACriticalSection()
	{
		InitializeCriticalSectionAndSpinCount(&CriticalSeciton, 4000);
	}

	__forceinline ~ACriticalSection()
	{
		DeleteCriticalSection(&CriticalSeciton);
	}

	__forceinline void Lock()
	{
		if (TryEnterCriticalSection(&CriticalSeciton) == 0)
		{
			EnterCriticalSection(&CriticalSeciton);
		}
	}

	__forceinline void UnLock()
	{
		LeaveCriticalSection(&CriticalSeciton);
	}
private:
	CRITICAL_SECTION CriticalSeciton;
};