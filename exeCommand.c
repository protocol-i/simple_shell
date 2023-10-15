#include "shell.h"
/**
 * executeCommand - Execute a command using PATH and avoid fork if the command doesn't exist.
 *
 * @param command: The command to execute.
 * @return: The exit status of the command if executed, or -1 if the command is not found.
 */
int executeCommand(const char* command)
{
	char* path = getenv("PATH");
    char* pathCopy = strdup(path);
    char* token = strtok(pathCopy, ":");
    while (token != NULL)
    {
        char commandPath[1024];
        snprintf(commandPath, sizeof(commandPath), "%s/%s", token, command);

        if (access(commandPath, X_OK) == 0)
	{
            
            pid_t pid = fork();
            if (pid == 0)
	    {
                execlp(command, command, NULL);
                perror("exec");
                exit(1);
            }
	    else if (pid < 0)
	    {
                perror("fork");
                return (1);
            }
	    else
	    {
                
                int status;
                wait(&status);
                return WEXITSTATUS(status);
            }
        }
	token = strtok(NULL, ":");
    }
    free(pathCopy);
    return (-1);
}
