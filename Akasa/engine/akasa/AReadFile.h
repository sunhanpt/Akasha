#ifndef __I_AREADFILE_H_INCLUDED__
#define __I_AREADFILE_H_INCLUDED__

#include "IReadFile.h"
#include "os.h"
#include "AkaString.h"
#include <stdio.h>

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
		virtual s32						Read(void* buffer, u32 sizeToRead) _AKA_OVERRIDE_;

		// 设置当前文件读取的位置，当relativeMovement为ture时，表示相对于当前位置；否则是相对于文件开头
		virtual bool					Seek(u32 finalPos, bool relativeMovement = false) _AKA_OVERRIDE_;

		// 返回文件大小

		virtual const u32				GetSize() _AKA_OVERRIDE_;

		// 返回当前位置
		virtual const u32				GetPos() _AKA_OVERRIDE_;

		// 
		virtual path&					GetFileName() _AKA_OVERRIDE_;

		bool							IsOpen() const { return Fin != nullptr; }

	private:
		void openFile();

		FILE * Fin;
		io::path m_fileName;
		int m_fileSize;
	};

}
}

#endif