#include "shell.h"
/**
 * main - Entry point for the shell program.
 * @arg_count: Argument count
 * @arg_vector: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_vector)
{
	ShellInfo shell_info[] = { SHELL_INFO_INIT };
	int file_descriptor = 2;

	if (arg_count == 2)
	{
		file_descriptor = open(arg_vector[1], O_RDONLY);

		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				fprintf(stderr, "%s: 0: Can't open %s\n", arg_vector[0], arg_vector[1]);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shell_info->readfd = file_descriptor;
	}

	return (EXIT_SUCCESS);
}
