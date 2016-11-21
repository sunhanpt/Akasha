#ifndef __AKA_IREADFILE_H_INCLUED__
#define __AKA_IREADFILE_H_INCLUED__

#include "IReferenceCounted.h"
#include "path.h"

namespace aka
{
	namespace io
	{
		class IReadFile: public virtual IReferenceCounted
		{
		public:
			IReadFile() {};
			virtual							~IReadFile() {};

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

		};
	}
}

#endif
