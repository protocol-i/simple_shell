#include "shell.h"
/**
 * prj_display_prompt - Display the custom shell prompt.
 */
void prj_display_prompt(void)
{
	printf("simple_shell$ ");
}

/**
 * prj_execute_command - Execute a shell command.
 * @command: The command to execute.
 */
void prj_execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			printf("Error: Command '%s' not found\n", command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 * prj_run_shell - Run the simple shell program.
 */
void prj_run_shell(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		prj_display_prompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\nGoodbye!\n");
			break;
		}
		if (command[strlen(command) - 1] == '\n')
		{
			command[strlen(command) - 1] = '\0';
		}

		if (strcmp(command, "exit") == 0)
		{
			printf("Exiting the shell...\n");
			break;
		}

		prj_execute_command(command);
	}
}

int main(void)
{
	int argc = 3;

	char* argv[] = {"./myprogram", "arg1", "arg2"};

	processCommandLineArguments(argc, argv);
	prj_run_shell();
        printEnvironment();
        printDir();

	return (0);
}
