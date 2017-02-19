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
		// ��ȡsizeToRead��С������(bytes)��buffer������ֵ��ʾ��ȡ�ĳ���
		virtual s32						Read(void* buffer, u32 sizeToRead) _AKA_OVERRIDE_;

		// ���õ�ǰ�ļ���ȡ��λ�ã���relativeMovementΪtureʱ����ʾ����ڵ�ǰλ�ã�������������ļ���ͷ
		virtual bool					Seek(u32 finalPos, bool relativeMovement = false) _AKA_OVERRIDE_;

		// �����ļ���С
		virtual u32						GetSize() _AKA_OVERRIDE_;

		// ���ص�ǰλ��
		virtual u32						GetPos() _AKA_OVERRIDE_;

		// 
		virtual path&					GetFileName() _AKA_OVERRIDE_;
	};

}
}

#endif