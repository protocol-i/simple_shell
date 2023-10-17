#include "shell.h"

/**
 * shell_exit - Exit the shell.
 * @info: The information struct.
 * Return: The exit status.
 */
int shell_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = _atoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->error_number = exit_status;
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}

/**
 * shell_change_directory - Change the current directory of the process.
 * @info: The information struct.
 * Return: Always 0.
 */
int shell_change_directory(info_t *info)
{
	char *current_directory, *new_directory, buffer[1024];
	int chdir_result;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
		_puts("TODO: >>getcwd failure message here<<\n");
	if (!info->argv[1])
	{
		new_directory = _getenv(info, "HOME=");
		if (!new_directory)
			chdir_result = chdir((new_directory = _getenv(info, "PWD=")) ? new_directory : "/");
		else
			chdir_result = chdir(new_directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_directory);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_result = chdir((new_directory = _getenv(info, "OLDPWD=")) ? new_directory : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - Display help information (not yet implemented).
 * @info: The information struct.
 * Return: Always 0.
 */
int shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

