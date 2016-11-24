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

	private:

	};

}
}

#endif