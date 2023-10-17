#include "shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: struct containing shell information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: string containing delimiter characters
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (*delimiters == c)
			return (1);
		delimiters++;
	}
	return (0);
}

/**
 * is_alpha - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if c is an alphabetic character, 0 otherwise
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the integer value or 0 if no valid integer is found
 */
int string_to_int(char *s)
{
	int i, sign = 1, flag = 0, result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	return (sign * result);
}
