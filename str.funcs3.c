#include "shell.h"

/**
 * splitStringByDelim - divides a string into words by delimiters. Repeated delimiters are ignored.
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **splitStringByDelim(char *str, char *d)
{
	int i, j, k, m, numWords = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return NULL;
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isDelimiter(str[i], d) && (isDelimiter(str[i + 1], d) || !str[i + 1]))
			numWords++;
	
	if (numWords == 0)
		return NULL;
	string = malloc((1 + numWords) * sizeof(char *));
	if (!string)
		return NULL;
	for (i = 0, j = 0; j < numWords; j++)
	{
		while (isDelimiter(str[i], d))
			i++;
		k = 0;
		while (!isDelimiter(str[i + k], d) && str[i + k])
			k++;
		string[j] = malloc((k + 1) * sizeof(char));
		if (!string[j])
		{
			for (k = 0; k < j; k++)
				free(string[k]);
			free(string);
			return NULL;
		}
		for (m = 0; m < k; m++)
			string[j][m] = str[i++];
		string[j][m] = 0;
	}
	string[j] = NULL;
	return string;
}

/**
 * splitStringByChar - divides a string into words by character delimiter
 * @str: the input string
 * @d: the character delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splitStringByChar(char *str, char d)
{
	int i, j, k, m, numWords = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return NULL;
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) || 
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numWords++;
	if (numWords == 0)
		return NULL;
	string = malloc((1 + numWords) * sizeof(char *));
	if (!string)
		return NULL;
	for (i = 0, j = 0; j < numWords; k++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		string[j] = malloc((k + 1) * sizeof(char));
		if (!string[j])
		{
			for (k = 0; k < j; k++)
				free(string[k]);
			free(string);
			return NULL;
		}
		for (m = 0; m < k; m++)
			string[j][m] = str[i++];
		string[j][m] = 0;
	}
	string[j] = NULL;
	return string;
}
