#pragma once
/************************************************************************/
/* Scope Lock
*  pengtong.pt 2018-10-28
*/
/************************************************************************/
#include "CriticalSection.h"

class AScopeLock
{
public:
	AScopeLock(ACriticalSection* InSynchObject):
		SynchObject(InSynchObject)
	{
		SynchObject->Lock();
	}
	~AScopeLock()
	{
		SynchObject->UnLock();
	}
private:
	// hidden these methods.
	AScopeLock(); 
	AScopeLock(const AScopeLock& InScopeLock);
	AScopeLock& operator= (const AScopeLock& InScopeLock)
	{
		return *this;
	}
private:
	ACriticalSection* SynchObject;
};