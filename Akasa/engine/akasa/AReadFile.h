#ifndef __I_AREADFILE_H_INCLUDED__
#define __I_AREADFILE_H_INCLUDED__

#include "IReadFile.h"
#include "os.h"
#include "AkaString.h"
#include <fstream>

using namespace std;


namespace aka
{
namespace io
{
	class AReadFile: public virtual IReadFile
	{
	public:
		AReadFile(const io::path& fileName);

		~AReadFile();
		// ��ȡsizeToRead��С������(bytes)��buffer������ֵ��ʾ��ȡ�ĳ���
		virtual s32						Read(void* buffer, u32 sizeToRead) = 0;

		// ���õ�ǰ�ļ���ȡ��λ�ã���relativeMovementΪtureʱ����ʾ����ڵ�ǰλ�ã�������������ļ���ͷ
		virtual bool					Seek(u32 finalPos, bool relativeMovement = false) = 0;

		// �����ļ���С
		virtual u32						GetSize() = 0;

		// ���ص�ǰλ��
		virtual u32						GetPos() = 0;

		// 
		virtual path&					GetFileName() = 0;

	private:
		ifstream Fin;
		io::path m_fileName;
	};

}
}

#endif