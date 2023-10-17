#include "shell.h"

/**
 * get_list_length - Determines the length of a linked list.
 * @head: Pointer to the first node of the list.
 *
 * Return: The length of the list.
 */
size_t get_list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

/**
 * convert_list_to_strings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: An array of strings.
 */
char **convert_list_to_strings(list_t *head)
{
	if (!head)
		return (NULL);

	size_t list_length = get_list_length(head);
	char **strings = malloc(sizeof(char *) * (list_length + 1));

	if (!strings)
		return (NULL);
	
	size_t index = 0;
	list_t *node = head;
	
	while (node)
	{
		strings[index] = strdup(node->str);
		if (!strings[index])
		{
			for (size_t i = 0; i < index; i++)
				free(strings[i]);
			free(strings);
			return (NULL);
		}

		node = node->next;
		index++;
	}

	strings[list_length] = NULL;
	return (strings);
}

/**
 * print_linked_list - Prints all elements of a linked list.
 * @head: Pointer to the first node of the list.
 *
 * Return: The number of nodes printed.
 */
size_t print_linked_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		printf("%ld: %s\n", head->num, (head->str ? head->str : "(nil)"));
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * find_node_with_prefix - Searches for a node in the list whose string starts with a given prefix (and optionally a specific character).
 * @node: Pointer to the first node of the list.
 * @prefix: The prefix string to match.
 * @next_char: The next character after the prefix to match.
 *
 * Return: A pointer to the matching node or NULL if no match is found.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char next_char)
{
	while (node)
	{
		char *p = starts_with(node->str, prefix);
		if (p && (next_char == -1 || *p == next_char))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * find_index_of_node - Gets the index of a specific node in the list.
 * @head: Pointer to the first node of the list.
 * @node: Pointer to the node.
 *
 * Return: The index of the node in the list or -1 if the node is not found.
 */
ssize_t find_index_of_node(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
            return (index);
		head = head->next;
		index++;
	}

	return (-1);
}
