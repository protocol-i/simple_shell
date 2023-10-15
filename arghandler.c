#include "shell.h"
/*
 * processCommandLineArguments - Process command-line arguments here
 * 
 * 
 * */
void processCommandLineArguments(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		printf("Argument %d: %s\n", i, argv[i]);
	}
}

int main(int argc, char* argv[])
{
	printf("Total number of command-line arguments: %d\n", argc);

	processCommandLineArguments(argc, argv);
	return (0);
}
