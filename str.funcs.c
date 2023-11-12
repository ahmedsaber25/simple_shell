#include "shell.h"

/**
 * stringLength - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of the string
 */
int stringLength(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}

/**
 * stringCompare - performs lexicographic comparison of two strings.
 * @string1: the first strang
 * @string2: the second strang
 *
 * Return: negative if string1 < string2, positive if string1 > string2, zero if string1 == string2
 */
int stringCompare(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * startsWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *startsWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * stringConcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *stringConcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return ret;
}
