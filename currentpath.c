#include "shell.h"
/**
 * printDir - Print the current working directory to the standard output.
 *
 * Description: retrieves the current working directory and prints it.
 */
void printDir(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}
