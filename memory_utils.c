#include "shell.h"
/**
 * mem_fill - Fill memory with a constant byte.
 * @mem: The pointer to the memory area.
 * @byte: The byte value to fill @mem with.
 * @size: The number of bytes to fill.
 * Return: A pointer to the memory area @mem.
 */
void *mem_fill(void *mem, char byte, size_t size)
{
	char *mem_ptr = (char *)mem;
	
	for (size_t i = 0; i < size; i++)
		mem_ptr[i] = byte;

	return (mem);
}

/**
 * free_string_array - Free an array of strings.
 * @str_array: An array of strings.
 */
void free_string_array(char **str_array)
{
	if (!str_array
			return;

			for (size_t i = 0; str_array[i] != NULL; i++)
			{
			free(str_array[i]);
			}
			free(str_array);
}

/**
 * mem_realloc - Reallocate a memory block.
 * @ptr: Pointer to the previous memory block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the reallocated memory block.
 */
void *mem_realloc(void *ptr, size_t old_size, size_t new_size)
{
if (!ptr)
return (malloc(new_size));

if (new_size == 0)
{
	free(ptr);

	return (NULL);
    }

if (new_size == old_size)
	return (ptr);

	void *new_ptr = malloc(new_size);
if (!new_ptr)
	return (NULL);

	size_t min_size = (new_size < old_size) ? new_size : old_size;
	memcpy(new_ptr, ptr, min_size);
	free(ptr);

	return (new_ptr);
}
