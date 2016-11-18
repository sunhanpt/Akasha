#include <iostream>
#include <fstream>
#include "AkaTypes.h"
using namespace std;
using namespace aka;

class AWriteFile
{
public:
	AWriteFile(const char * str);
	~AWriteFile();
	void Log(char * str);
	void Flush();

private:
	ofstream * fout;
};

AWriteFile::AWriteFile(const char * str)
{
	fout = new ofstream(str, ios::app);
}

AWriteFile::~AWriteFile()
{
	fout->close();
	delete fout;
}

void AWriteFile::Log(char * str)
{
	(*fout) << str;
}

void AWriteFile::Flush()
{
	fout->flush();
}

int main()
{
	AWriteFile * writeFile = new AWriteFile("D:\\write.txt");
	writeFile->Log("hahaha\n");
	writeFile->Log("hahahahahaha\n");
	writeFile->Log("hahahahahahahahaha\n");
	delete writeFile;
	return 0;
}