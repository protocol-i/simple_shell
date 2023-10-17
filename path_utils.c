#include "shell.h"

/**
 * is_executable - Determines if a file is an executable command.
 * @path: Path to the file.
 * Return: true if it's an executable, false otherwise.
 */
bool is_executable(const char *path)
{
	struct stat st;
	if (!path || stat(path, &st) != 0)
		return (false);
	return (st.st_mode & S_IXUSR) ? true : false;
}

/**
 * copy_path_segment - Duplicates a segment of characters from a PATH string.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 * Return: Pointer to the new buffer.
 */
char *copy_path_segment(const char *pathstr, size_t start, size_t stop)
{
	static char buf[1024];
	size_t i = 0, k = 0;
	for (i = start; i < stop && pathstr[i] != '\0'; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}
	buf[k] = '\0';
	return buf;
}

/**
 * find_executable_path - Finds the full path of a command in the PATH string.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 * Return: Full path of the command if found, or NULL.
 */
char *find_executable_path(const char *pathstr, const char *cmd)
{
	size_t i = 0, curr_pos = 0;
	char *path;

	if (!pathstr || !cmd)
		return (NULL);

	if (strlen(cmd) > 2 && strncmp(cmd, "./", 2) == 0)
	{
		if (is_executable(cmd))
		{
			return (strdup(cmd));
		}
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = copy_path_segment(pathstr, curr_pos, i);
			if (*path == '\0')
			{
				strcat(path, cmd);
			}
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_executable(path))
			{
				return (strdup(path));
			}
			if (!pathstr[i])
			{
				break;
			}
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
