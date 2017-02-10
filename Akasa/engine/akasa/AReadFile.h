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
		// 读取sizeToRead大小的数据(bytes)到buffer，返回值表示读取的长度
		virtual s32						Read(void* buffer, u32 sizeToRead) = 0;

		// 设置当前文件读取的位置，当relativeMovement为ture时，表示相对于当前位置；否则是相对于文件开头
		virtual bool					Seek(u32 finalPos, bool relativeMovement = false) = 0;

		// 返回文件大小
		virtual u32						GetSize() = 0;

		// 返回当前位置
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