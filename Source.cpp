#include "Utility.h"
#include "Test.h"

#define DEBUG 0

int main(int argc, char *argv[])
{
#if DEBUG
	testProcessInput();

	return 0;
#endif

	if(argc == 1)
		openFile("log.txt");
	else if(argc > 1)
		openFile(argv[1]);
}