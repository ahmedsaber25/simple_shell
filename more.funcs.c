#include "shell.h"

/**
 * isInteractiveMode - checks if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info) 
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter
 * @c: the character to check
 * @delimiters: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiters) 
{
    while (*delimiters) 
    {
     if (*delimiters++ == c)
      return (1);
    }
    return (0);
}

/**
 * isAlphabetic - checks for an alphabetic character
 * @charInput: The character to evaluate
 * Return: 1 if charInput is alphabetic, 0 otherwise
 */
int isAlphabetic(int c) 
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && charInput <= 'Z')) 
    return (1); 
else 
    return (0);
}

/**
 * convertToInteger - converts a string to an integer
 * @string: the string to convert
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int convertToInteger(char *string) 
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; string[i] != '\0' && flag != 2; i++) 
    {
     if (string[i] == '-') 
     {
       sign *= -1;
     }
     if (string[i] >= '0' && string[i] <= '9') 
     {
        flag = 1;
        result *= 10;
        result += (string[i] - '0');
     } 
     else if (flag == 1) 
             flag = 2;
    }
    if (sign == -1) 
           output = -result; 
    else 
        output = result;

    return (output);
}
