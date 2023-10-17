#include "shell.h"
/**
 * printEnvironment - Print environment variables to the standard output.
 * char *envp: An array of strings containing environment variables.
 *
 * * Description:Iterate through and print environment variables.
 */
void printEnvironment(char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("\n%s", envp[i]);
	}
}
