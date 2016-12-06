#ifndef __AKA_IWRITEFILE_H_INCLUED__
#define __AKA_IWRITEFILE_H_INCLUED__

#include "IReferenceCounted.h"
#include "path.h"

namespace aka
{
	namespace io
	{
		class IWriteFile:public virtual IReferenceCounted
		{
		public:
			IWriteFile() {};
			virtual						~IWriteFile() {};
			// дbuffer
			virtual bool				Write(const void* buffer) = 0;
			// дbytes���ļ���sizeToWrite��ʾbuffer��byte����
			virtual bool				Write(const void* buffer, u32 sizeToWrite) = 0;		
			// Seek���ļ���ĳ���ط���finalPos��ʾλ�ã� relativeMovementΪtrue��ʾ��������ڵ�λ�ã������ʾ�����ļ���ʼ��λ��
			virtual	bool				Seek(long finalPos, bool relativeMovement = false) = 0;
			// �������ڵ�λ�ã�bytes�ĸ���
			virtual long				GetPos() = 0;
			// �����ļ�������(����·��)
			virtual const path& GetFileName() const = 0;
			// ˢ���ļ�����
			virtual void Flush() = 0;
			// �ر��ļ�
			virtual void Close() = 0;
		};
	}
}

#endif