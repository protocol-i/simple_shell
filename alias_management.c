#include "shell.h"

/**
 * display_history - Displays the history list with line numbers.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias by name.
 * @info: Parameter struct.
 * @name: The alias to unset.
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *name)
{
	char *equals;
	char c;
	int result;

	equals = _strchr(name, '=');
	if (!equals)
		return (1);
	c = *equals;
	*equals = '\0';
	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, name, -1)));
	*equals = c;

	return (result);
}

/**
 * set_alias - Set an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias to set.
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *equals;

	equals = _strchr(str, '=');
	if (!equals)
		return (1);
	if (!*++equals)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *equals = NULL;
	char *alias = NULL;

	if (node)
	{
		equals = _strchr(node->str, '=');
		for (alias = node->str; alias <= equals; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equals + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias - Handle alias operations.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int handle_alias(info_t *info)
{
	int i = 0;
	char *equals = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals = _strchr(info->argv[i], '=');
		if (equals)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
