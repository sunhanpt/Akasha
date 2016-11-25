#ifndef __I_AWRITEFILE_H_INCLUDED__
#define __I_AWRITEFILE_H_INCLUDED__

#include "IWriteFile.h"
#include "os.h"
#include "AkaString.h"
#include <fstream>

using namespace std;


namespace aka
{
namespace io
{
	class AWriteFile: public virtual IWriteFile
	{
	public:
		AWriteFile(const io::path& fileName, bool append);

		virtual ~AWriteFile();
		// override
		virtual bool				Write(const void* buffer);
		// дbytes���ļ���sizeToWrite��ʾbuffer��byte����
		virtual bool				Write(const void* buffer, u32 sizeToWrite);
		// Seek���ļ���ĳ���ط���finalPos��ʾλ�ã� relativeMovementΪtrue��ʾ��������ڵ�λ�ã������ʾ�����ļ���ʼ��λ��
		virtual	bool				Seek(long finalPos, bool relativeMovement = false);
		// �������ڵ�λ�ã�bytes�ĸ���
		virtual long				GetPos();
		// �����ļ�������(����·��)
		virtual const path& GetFileName() const;
		// ˢ���ļ�����
		virtual bool Flush();
	protected:

	private:
		ofstream * FOUT;
	};

}
}

#endif