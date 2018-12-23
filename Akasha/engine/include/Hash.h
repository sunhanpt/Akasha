#pragma once

#include "TypeDefines.h"
#include "CRC32.h"

class AHash
{
public:
	AHash(const char* sStr)
		: m_HashValue(0)
	{
		m_HashValue = StringToHash(sStr);
	}

	AHash() : m_HashValue(0) {}

	~AHash() {}

	const AHash& operator=(const AHash& Other)
	{
		this->m_HashValue = Other.m_HashValue;
		return *this;
	}

	bool operator==(const AHash& Other)
	{
		return m_HashValue == Other.m_HashValue;
	}

	void SetHashString(const char* sStr)
	{
		m_HashValue = StringToHash(sStr);
	}

	uint32 GetHashValue()
	{
		return m_HashValue;
	}

private:
	uint32 m_HashValue;

	__forceinline uint32 StringToHash(const char* str)
	{
		uint32 strLength = (uint32)strlen(str);
		return FCrc::MemCrc(str, strLength);
	}
};
