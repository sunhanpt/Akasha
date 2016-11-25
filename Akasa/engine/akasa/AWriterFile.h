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
		// 写bytes到文件，sizeToWrite表示buffer的byte长度
		virtual bool				Write(const void* buffer, u32 sizeToWrite);
		// Seek到文件的某个地方，finalPos表示位置， relativeMovement为true表示相对于现在的位置，否则表示距离文件开始的位置
		virtual	bool				Seek(long finalPos, bool relativeMovement = false);
		// 返回现在的位置，bytes的个数
		virtual long				GetPos();
		// 返回文件的名称(包括路径)
		virtual const path& GetFileName() const;
		// 刷新文件缓存
		virtual bool Flush();
	protected:

	private:
		ofstream * FOUT;
	};

}
}

#endif