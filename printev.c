#include "shell.h"
/* 
 * printEnvironment- to print environment variables
 */
void printEnvironment(char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("\n%s", envp[i]);
	}
}
