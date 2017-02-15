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
	openFile();
}

AReadFile::~AReadFile()
{
	fclose(Fin);
}

//////////////////////////////////* override method *////////////////////////////////////////
s32	AReadFile::Read(void* buffer, u32 sizeToRead)
{

}

bool AReadFile::Seek(u32 finalPos, bool relativeMovement = false)
{

}

const u32 AReadFile::GetSize()
{
	return m_fileSize;
}

const u32	AReadFile::GetPos()
{
	ftell(Fin);
}

path& AReadFile::GetFileName()
{

}

///////////////////////////////////* private method *///////////////////////////////////////
void AReadFile::openFile()
{
	if (!m_fileName.c_str() || strlen(m_fileName.c_str()) <= 0) {
		Fin = nullptr;
		return;
	}
	Fin = fopen(m_fileName.c_str(), "rb");
	if (!Fin) {
		return;
	}
	fseek(Fin, 0, SEEK_END);
	m_fileSize = GetSize();
	fseek(Fin, 0, SEEK_SET);
}

}
}


