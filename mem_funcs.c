#include "shell.h"

/**
 * _fill_memory - fills memory with a constant byte
 * @string: the pointer to the memory area
 * @b: the byte to fill *string with
 * @n: the amount of bytes to be filled
 * Return: a pointer to the memory area mem_area
 */
char *_fill_memory(char *string, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		string[i] = b;
	return string;
}

/**
 * ffree - frees an array of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous block of memory
 * @old_block_size: byte size of the previous block
 * @new_block_size: byte size of the new block
 *
 * Return: pointer to the updated block of memory
 */
void *_realloc(void *ptr, unsigned int old_block_size, unsigned int new_block_size)
{
	char *p;

	if (!ptr)
		return malloc(new_block_size);
	if (!new_block_size)
		return (free(ptr), NULL);
	if (new_block_size == old_block_size)
		return ptr;
	
	p = malloc(new_block_size);
	if (!p)
		return NULL;

	old_block_size = old_block_size < new_block_size ? old_block_size : new_block_size;
	while (old_block_size--)
		new_ptr[old_block_size] = ((char *)ptr)[old_block_size];
	free(ptr);
	return p;
}
