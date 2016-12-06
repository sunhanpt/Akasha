#include <iostream>
#include <fstream>
#include "AkaTypes.h"
#include "os.h"
#include "ALogger.h"
using namespace std;
using namespace aka;


int main()
{
	ALogger * logger = new ALogger();
	logger->OpenLogFile("D:\\text.txt");
	os::Printer::Logger = logger;
	os::Printer::Log("hhhhhhhhhaaaaaaa\n");
	return 0;
}