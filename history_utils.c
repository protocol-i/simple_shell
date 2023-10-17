#include "shell.h"

/**
 * get_history_file - Get the path to the history file.
 * @info: Parameter struct (not used in this function).
 *
 * Return: Allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
	char *home_dir, *history_file_path;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	history_file_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!history_file_path)
	{
		free(home_dir);
		return (NULL);
	}
	history_file_path[0] = 0;
	_strcpy(history_file_path, home_dir);
	_strcat(history_file_path, "/");
	_strcat(history_file_path, HIST_FILE);

	free(home_dir);
	return (history_file_path);
}

/**
 * write_history - Write command history to a file.
 * @info: Parameter struct containing command history.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *history_file_name = get_history_file(info);
	list_t *history_node = NULL;

	if (!history_file_name)
		return (-1);

	fd = open(history_file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file_name);

	if (fd == -1)
		return (-1);

	for (history_node = info->history; history_node; history_node = history_node->next)
	{
		_putsfd(history_node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Read command history from a file.
 * @info: Parameter struct to store command history.
 *
 * Return: The number of history entries read on success, 0 on failure.
 */
int read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, read_len, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
	free(file_name);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &file_stat))
		file_size = file_stat.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);

	read_len = read(fd, buffer, file_size);
	buffer[file_size] = 0;

	if (read_len <= 0)
		return (free(buffer), 0);

	close(fd);

	for (i = 0; i < file_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(info, buffer + last, line_count++);

	free(buffer);
	info->histcount = line_count;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);       

	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Add an entry to the history linked list.
 * @info: Parameter struct.
 * @buffer: Buffer containing the history entry.
 * @line_count: The history line count (histcount).
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - Renumber the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
