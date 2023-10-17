#include "shell.h"

/**
 * get_environment - Return a copy of the environment variables.
 * @info: Pointer to the info_t structure.
 *
 * Return: Array of environment variables.
 */
char **get_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environment);
}

/**
 * unset_environment_variable - Remove an environment variable.
 * @info: Pointer to the info_t structure.
 * @variable: The environment variable to unset.
 *
 * Return: 1 on success, 0 on failure.
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *prefix;

	if (!node || !variable)
		return (0);

	while (node)
	{
		prefix = starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_environment_variable - Set or modify an environment variable.
 * @info: Pointer to the info_t structure.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: 1 on success, 0 on failure.
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *prefix;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (0);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	node = info->env;
	while (node)
	{
		prefix = starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (1);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (1);
}

