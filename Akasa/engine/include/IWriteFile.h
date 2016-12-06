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
			// 写buffer
			virtual bool				Write(const void* buffer) = 0;
			// 写bytes到文件，sizeToWrite表示buffer的byte长度
			virtual bool				Write(const void* buffer, u32 sizeToWrite) = 0;		
			// Seek到文件的某个地方，finalPos表示位置， relativeMovement为true表示相对于现在的位置，否则表示距离文件开始的位置
			virtual	bool				Seek(long finalPos, bool relativeMovement = false) = 0;
			// 返回现在的位置，bytes的个数
			virtual long				GetPos() = 0;
			// 返回文件的名称(包括路径)
			virtual const path& GetFileName() const = 0;
			// 刷新文件缓存
			virtual void Flush() = 0;
			// 关闭文件
			virtual void Close() = 0;
		};
	}
}

#endif