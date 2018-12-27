#pragma once
#include "TypeDefines.h"
#include <vector>

struct FBaseShaderResourceTable
{
	/** Bits indicating which resource tables contain resources bound to this shader. */
	uint32 ResourceTableBits;

	/** Mapping of bound SRVs to their location in resource tables. */
	std::vector<uint32> ShaderResourceViewMap;

	/** Mapping of bound sampler states to their location in resource tables. */
	std::vector<uint32> SamplerMap;

	/** Hash of the layouts of resource tables at compile time, used for runtime validation. */
	std::vector<uint32> ResourceTableLayoutHashes;

	FBaseShaderResourceTable()
		: ResourceTableBits(0)
	{
	}

	friend bool operator==(const FBaseShaderResourceTable& A, const FBaseShaderResourceTable& B)
	{
		bool bEqual = true;
		bEqual &= (A.ResourceTableBits == B.ResourceTableBits);
		bEqual &= (A.ShaderResourceViewMap.size() == B.ShaderResourceViewMap.size());
		bEqual &= (A.SamplerMap.size() == B.SamplerMap.size());
		bEqual &= (A.ResourceTableLayoutHashes.size() == B.ResourceTableLayoutHashes.size());
		if (!bEqual)
		{
			return false;
		}
		
		bEqual &= (memcmp(A.ShaderResourceViewMap.data(), B.ShaderResourceViewMap.data(), sizeof(uint32) * A.ShaderResourceViewMap.size()) == 0);
		bEqual &= (memcmp(A.SamplerMap.data(), B.SamplerMap.data(), sizeof(uint32) * A.SamplerMap.size()) == 0);
		bEqual &= (memcmp(A.ResourceTableLayoutHashes.data(), B.ResourceTableLayoutHashes.data(), sizeof(uint32) * A.ResourceTableLayoutHashes.size()) == 0);

		return bEqual;
	}
};