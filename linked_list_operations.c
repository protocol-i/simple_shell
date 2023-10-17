#include "shell.h"
/**
 * add_node_at_start - Adds a node to the start of the list.
 * @head_ptr: Pointer to the head node.
 * @str: String data for the new node.
 * @num: Numeric index used by history.
 *
 * Return: A pointer to the newly added node.
 */
list_t *add_node_at_start(list_t **head_ptr, const char *str, int num)
{
	list_t *new_node;

	if (!head_ptr)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head_ptr;
	*head_ptr = new_node;
	return (new_node);
}

/**
 * add_node_at_end - Adds a node to the end of the list.
 * @head_ptr: Pointer to the head node.
 * @str: String data for the new node.
 * @num: Numeric index used by history.
 *
 * Return: A pointer to the newly added node.
 */
list_t *add_node_at_end(list_t **head_ptr, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head_ptr)
		return (NULL);

	node = *head_ptr;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}

/**
 * print_string_list - Prints only the string elements of a list.
 * @head: Pointer to the head node.
 *
 * Return: The number of nodes printed.
 */
size_t print_string_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		printf("%ld: %s\n", head->num, (head->str ? head->str : "(nil)"));
		head = head->next;
		count++;
	}
	return (count;)
}

/**
 * delete_node_at_index - Deletes a node at a given index.
 * @head_ptr: Pointer to the head node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head_ptr, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!index)
	{
		node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head_ptr;

	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_string_list - Frees all nodes of a list.
 * @head_ptr: Pointer to the head node.
 *
 * Return: Void.
 */
void free_string_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
