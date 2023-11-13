#include "shell.h"

/**
 * count_list - determines the number of nodes in a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t count_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = count_list(head), j;
	char **string_array;
	char *str;

	if (!head || !i)
		return (NULL);
	string_array = malloc(sizeof(char *) * (i + 1));
	if (!string_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(stringLength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(string_array[j]);
			free(string_array);
			return (NULL);
		}
		str = copyString(str, node->str);
		string_array[i] = string;
	}
	string_array[i] = NULL;
	return string_array;
}

/**
 * print_list - prints all elements of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts (convertToText (h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts (h->str ? h->str : "(nil)");
		_puts ("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * find_node_starts_with - returns the node whose string starts with a prefix
 * @list_head: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		list_head = list_head->next;
	}
	return (NULL);
}

/**
 * obtain_node_index - gets the index of a particular node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t obtain_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		i++;
	}
	return (-1);
}
