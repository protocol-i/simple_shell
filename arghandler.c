#include "shell.h"
/**
 * processCommandLineArguments - Process command-line arguments and print them.
 * Description: handles the command line arguments.
 */
void processCommandLineArguments(void)
{
	for (int i = 1; i < argc; i++)
	{
		printf("Argument %d: %s\n", i, argv[i]);
	}
}
