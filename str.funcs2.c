#include "shell.h"

/**
 * copyStringWithLimit - copies a string up to a specified limit
 * @destination: the destination string to be copied to
 * @source: the source string
 * @limit: the maximum number of characters to be copied
 * Return: the concatenated string
 */
char *copyStringWithLimit(char *destination, char *source, int n)
{
    int i, j;
    char *string = destination;

    index = 0;
    while (source[i] != '\0' && i < n - 1)
    {
    destination[i] = source[i];
    i++;
    }
    if (i < n)
    {
     j = i;
     while (j < n)
     {
      destination[j] = '\0';
      j++;
     }
    }
    return (string);
}

/**
 * concatenateStringWithLimit - concatenates two strings up to a specified limit
 * @destination: the first string
 * @source: the second string
 * @n: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *concatenateStringWithLimit(char *destination, char *source, int n)
{
    int i, j;
    char *string = destination;

    i = 0;
    j = 0;

    while (destination[i] != '\0')
    i++;
    while (source[j] != '\0' && j < n)
    destination[i] = source[j];
    i++;
    j++;
    }
    if (j < n)
    destination[i] = '\0';
    return (string);
}

/**
 * findCharacter - locates a character in a string
 * @string: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the memory area containing the character
 */
char *findCharacter(char *string, char c)
{
 do {
  if (*string == c)
  return (string);
} while (*string++ != '\0');

    return (NULL);
}
