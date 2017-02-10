#include "AReadFile.h"

namespace aka
{
namespace io
{

AReadFile::AReadFile(const io::path & fileName)
{
#ifdef _DEBUG
	this->setDebugName("AReadFile");
#endif
	m_fileName = fileName;

}

AReadFile::~AReadFile()
{
}

s32	AReadFile::Read(void* buffer, u32 sizeToRead)
{

}

bool AReadFile::Seek(u32 finalPos, bool relativeMovement = false)
{

}

u32	AReadFile::GetSize()
{

}

u32	AReadFile::GetPos()
{

}

path& AReadFile::GetFileName()
{

}



}
}


