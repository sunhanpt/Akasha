#include "stdafx.h"

#include "CRC32.H"

class CCRC32 {

public:
	CCRC32(void);
	~CCRC32(void);

	void Initialize(void);

	bool FileCRC(const char *sFileName, unsigned int *iOutCRC);
	bool FileCRC(const char *sFileName, unsigned int *iOutCRC, size_t iBufferSize);
	unsigned int FileCRC(const char *sFileName);
	unsigned int FileCRC(const char *sFileName, size_t iBufferSize);

	unsigned int FullCRC(const unsigned char *sData, size_t iDataLength);
	void FullCRC(const unsigned char *sData, size_t iLength, unsigned int *iOutCRC);

	void PartialCRC(unsigned int *iCRC, const unsigned char *sData, size_t iDataLength);

private:
	unsigned int Reflect(unsigned int iReflect, const char cChar);
	unsigned int iTable[256]; // CRC lookup table array.
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
This function initializes "CRC Lookup Table". You only need to call it once to
initalize the table before using any of the other CRC32 calculation functions.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCRC32::CCRC32(void)
{
	this->Initialize();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCRC32::~CCRC32(void)
{
	//No destructor code.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
This function initializes "CRC Lookup Table". You only need to call it once to
initalize the table before using any of the other CRC32 calculation functions.
*/

void CCRC32::Initialize(void)
{
	//0x04C11DB7 is the official polynomial used by PKZip, WinZip and Ethernet.
	unsigned int iPolynomial = 0x04C11DB7;

	memset(&this->iTable, 0, sizeof(this->iTable));

	// 256 values representing ASCII character codes.
	for (int iCodes = 0; iCodes <= 0xFF; iCodes++)
	{
		this->iTable[iCodes] = this->Reflect(iCodes, 8) << 24;

		for (int iPos = 0; iPos < 8; iPos++)
		{
			this->iTable[iCodes] = (this->iTable[iCodes] << 1)
				^ ((this->iTable[iCodes] & (1 << 31)) ? iPolynomial : 0);
		}

		this->iTable[iCodes] = this->Reflect(this->iTable[iCodes], 32);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Reflection is a requirement for the official CRC-32 standard.
You can create CRCs without it, but they won't conform to the standard.
*/

unsigned int CCRC32::Reflect(unsigned int iReflect, const char cChar)
{
	unsigned int iValue = 0;

	// Swap bit 0 for bit 7, bit 1 For bit 6, etc....
	for (int iPos = 1; iPos < (cChar + 1); iPos++)
	{
		if (iReflect & 1)
		{
			iValue |= (1 << (cChar - iPos));
		}
		iReflect >>= 1;
	}

	return iValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Calculates the CRC32 by looping through each of the bytes in sData.

Note: For Example usage example, see FileCRC().
*/

void CCRC32::PartialCRC(unsigned int *iCRC, const unsigned char *sData, size_t iDataLength)
{
	while (iDataLength--)
	{
		//If your compiler complains about the following line, try changing
		//	each occurrence of *iCRC with ((unsigned int)*iCRC).

		*iCRC = (*iCRC >> 8) ^ this->iTable[(*iCRC & 0xFF) ^ *sData++];
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Returns the calculated CRC32 (through iOutCRC) for the given string.
*/

void CCRC32::FullCRC(const unsigned char *sData, size_t iDataLength, unsigned int *iOutCRC)
{
	((unsigned int)*iOutCRC) = 0xffffffff; //Initilaize the CRC.

	this->PartialCRC(iOutCRC, sData, iDataLength);

	((unsigned int)*iOutCRC) ^= 0xffffffff; //Finalize the CRC.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Returns the calculated CRC23 for the given string.
*/

unsigned int CCRC32::FullCRC(const unsigned char *sData, size_t iDataLength)
{
	unsigned int iCRC = 0xffffffff; //Initilaize the CRC.

	this->PartialCRC(&iCRC, sData, iDataLength);

	return(iCRC ^ 0xffffffff); //Finalize the CRC and return.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Calculates the CRC32 of a file using the a user defined buffer.

Note: The buffer size DOES NOT affect the resulting CRC,
it has been provided for performance purposes only.
*/

bool CCRC32::FileCRC(const char *sFileName, unsigned int *iOutCRC, size_t iBufferSize)
{
	((unsigned int)*iOutCRC) = 0xffffffff; //Initilaize the CRC.

	FILE *fSource = NULL;
	unsigned char *sBuf = NULL;
	size_t iBytesRead = 0;

	if ((fSource = fopen(sFileName, "rb")) == NULL)
	{
		return false; //Failed to open file for read access.
	}

#ifdef _USE_GLOBAL_MEMPOOL
	if (!(sBuf = (unsigned char *)pMem->Allocate(iBufferSize, 1))) //Allocate memory for file buffering.
#else
	if (!(sBuf = (unsigned char *)malloc(iBufferSize))) //Allocate memory for file buffering.
#endif
	{
		fclose(fSource);
		return false; //Out of memory.
	}

	while ((iBytesRead = fread(sBuf, sizeof(char), iBufferSize, fSource)))
	{
		this->PartialCRC(iOutCRC, sBuf, iBytesRead);
	}

#ifdef _USE_GLOBAL_MEMPOOL
	pMem->Free(sBuf);
#else
	free(sBuf);
#endif

	fclose(fSource);

	((unsigned int)*iOutCRC) ^= 0xffffffff; //Finalize the CRC.

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Calculates the CRC32 of a file using the a default buffer size of 1MB.
*/

unsigned int CCRC32::FileCRC(const char *sFileName)
{
	unsigned int iCRC;
	if (this->FileCRC(sFileName, &iCRC, 1048576))
	{
		return iCRC;
	}
	else return 0xffffffff; //While we return this as an error code, it is infact a valid CRC!
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Calculates the CRC32 of a file using the a default buffer size of 1MB.

Note: The buffer size DOES NOT affect the resulting CRC,
it has been provided for performance purposes only.
*/

unsigned int CCRC32::FileCRC(const char *sFileName, size_t iBufferSize)
{
	unsigned int iCRC;
	if (this->FileCRC(sFileName, &iCRC, iBufferSize))
	{
		return iCRC;
	}
	else return 0xffffffff; //While we return this as an error code, it is infact a valid CRC!
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Calculates the CRC32 of a file using the a default buffer size of 1MB.
*/

bool CCRC32::FileCRC(const char *sFileName, unsigned int *iOutCRC)
{
	return this->FileCRC(sFileName, iOutCRC, 1048576);
}


//////////////////////////////////////////////////////////////////////////
static CCRC32 g_CRC32;

uint32 FCrc::MemCrc(const void* Data, int32 Length)
{
	unsigned int iCRC = g_CRC32.FullCRC((const unsigned char*)Data, Length);
	return (uint32)iCRC;
}

uint32 FCrc::FileCrc(const char* szFileName)
{
	unsigned int iCRC = 0;
	g_CRC32.FileCRC(szFileName, &iCRC);
	return iCRC;
}