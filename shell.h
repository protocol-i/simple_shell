#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
void prj_run_shell(void);
void prj_execute_command(const char *command);
void prj_display_prompt(void);
void printEnvironment;

#endif

