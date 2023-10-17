#include "shell.h"

/**
 * shell_buffer_input - Buffer input for chained commands
 * @info: Pointer to the parameter structure
 * @buffer: Address of the input buffer
 * @length: Address of the buffer length variable
 *
 * Return: Number of bytes read
 */
ssize_t shell_buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t buffer_length = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, shell_sigint_handler);

		bytes_read = getline(buffer, &buffer_length, stdin);

		bytes_read = shell_getline(info, buffer, &buffer_length);
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			shell_remove_comments(*buffer);
			shell_build_history_list(info, *buffer, info->histcount++);
			{
				*length = bytes_read;
				info->cmd_buffer = buffer;
			}
		}
	}
	return bytes_read;
}

/**
 * shell_get_input - Get the next line of input
 * @info: Pointer to the parameter structure
 *
 * Return: Number of bytes read
 */
ssize_t shell_get_input(info_t *info)
{
	static char *buffer;
	static size_t buffer_index, buffer_length, len;
	ssize_t bytes_read = 0;
	char **input_buffer = &(info->arg);
	char *ptr;

	shell_putchar(BUF_FLUSH);
	bytes_read = shell_buffer_input(info, &buffer, &buffer_length);
	if (bytes_read == -1)
		return -1;
	if (buffer_length)
	{
		buffer_index = len;
		ptr = buffer + buffer_index;

		shell_check_chain(info, buffer, &buffer_index, len, buffer_length);
		while (buffer_index < buffer_length)
		{
			if (shell_is_chain(info, buffer, &buffer_index))
				break;
			buffer_index++;
		}

		len = buffer_index + 1;
		if (len >= buffer_length)
		{
			buffer_index = buffer_length = 0;
			info->cmd_buffer_type = CMD_NORM;
		}

		*input_buffer = ptr;

		return _strlen(ptr);
	}

	*input_buffer = buffer;
	return bytes_read;
}

/**
 * shell_read_buffer - Read data into a buffer
 * @info: Pointer to the parameter structure
 * @buffer: Buffer for storing data
 * @index: Size variable for tracking data size
 *
 * Return: Number of bytes read
 */
ssize_t shell_read_buffer(info_t *info, char *buffer, size_t *index)
{
	ssize_t bytes_read = 0;

	if (*index)
		return 0;
	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*index = bytes_read;
	return bytes_read;
}

/**
 * shell_getline - Get the next line of input from STDIN
 * @info: Pointer to the parameter structure
 * @ptr: Address of the pointer to the buffer, preallocated or NULL
 * @length: Size of the preallocated buffer if not NULL
 *
 * Return: Length of the input
 */
int shell_getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buffer_index, buffer_length;
	size_t k;
	ssize_t bytes_read, input_length;
	char *buffer_ptr = NULL, *new_ptr = NULL, *c;

	buffer_ptr = *ptr;
	if (buffer_ptr && length)
		input_length = *length;
	if (buffer_index == buffer_length)
		buffer_index = buffer_length = 0;

	bytes_read = shell_read_buffer(info, buffer, &buffer_length);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
		return -1;

	c = _strchr(buffer + buffer_index, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_ptr = _realloc(buffer_ptr, input_length, input_length ? input_length + k : k + 1);
	if (!new_ptr)
		return buffer_ptr ? free(buffer_ptr), -1 : -1;

	if (input_length)
		_strncat(new_ptr, buffer + buffer_index, k - buffer_index);
	else
		_strncpy(new_ptr, buffer + buffer_index, k - buffer_index + 1);

	input_length += k - buffer_index;
	buffer_index = k;
	buffer_ptr = new_ptr;

	if (length)
		*length = input_length;
	*ptr = buffer_ptr;
	return input_length;
}

/**
 * shell_sigint_handler - Signal handler to block Ctrl-C
 * @sig_num: The signal number
 *
 * Return: Void
 */
void shell_sigint_handler(__attribute__((unused))int sig_num)
{
	shell_puts("\n");
	shell_puts("$ ");
	shell_putchar(BUF_FLUSH);
}
