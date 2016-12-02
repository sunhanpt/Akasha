#include "AWriterFile.h"

namespace aka
{
namespace io
{

AWriteFile::AWriteFile(const io::path & fileName, bool append)
{
#ifdef _DEBUG
	this->setDebugName("AWriteFile");
#endif
	if (append) {
		FOUT.open(fileName.c_str(),ios::app);
	}
	else {
		FOUT.open(fileName.c_str());
	}
	m_fileName = fileName;
}

AWriteFile::~AWriteFile()
{
	FOUT.close();
}

bool AWriteFile::Write(const void * buffer)
{
	if (FOUT.is_open()) {
		FOUT << buffer;
		if (FOUT.fail() == false) {
			return true;
		}
	}
	return false;
}

bool AWriteFile::Write(const void* buffer, u32 sizeToWrite)
{
	if (FOUT.is_open()) {
		FOUT.write((char *)buffer, sizeToWrite);
		if (FOUT.fail() == false) {
			return true;
		}
	}
	return false;
}

bool AWriteFile::Seek(long finalPos, bool relativeMovement /* = false */)
{
	if (relativeMovement) {
		FOUT.seekp(finalPos, ios::cur);
	}
	else {
		FOUT.seekp(finalPos, ios::beg);
	}
	if (FOUT.fail() == false) {
		return true;
	}
	return false;
}

long AWriteFile::GetPos()
{
	if (!FOUT.is_open()) {
		return 0;
	}
	return FOUT.tellp();
}

const path & AWriteFile::GetFileName() const
{
	return m_fileName;
}



}
}


