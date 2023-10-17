#include "shell.h"
/**
 * clear_info - Initialize info_t structure with default values.
 * @info: Pointer to the info_t structure to initialize.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initialize info_t structure based on command-line arguments.
 * @info: Pointer to the info_t structure to initialize.
 * @av: Command-line argument vector.
 */
void set_info(info_t *info, char **av)
{
	int arg_count = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (arg_count = 0; info->argv && info->argv[arg_count]; arg_count++);
		info->argc = arg_count;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Free allocated memory associated with info_t structure fields.
 * @info: Pointer to the info_t structure.
 * @free_all: Boolean to specify whether to free all fields or only some.
 */
void free_info(info_t *info, int free_all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;

		bfree((void **)info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
