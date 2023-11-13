#include "shell.h"

/**
 * errorToInteger - converts a string to an integer
 * @string: the string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 *        -1 on error
 */
int errorToInteger(char *string) 
{
    int i = 0;
    unsigned long int result = 0;

    if (*string == '+')
        string++;
    for (i = 0; string[i] != '\0'; i++) 
    {
        if (string[i] >= '0' && string[i] <= '9') 
        {
            result *= 10;
            result += (string[i] - '0');
            if (result > INT_MAX)
                return (-1);
        } 
        else 
            return (-1);
    }
    return ((int)result);
}

/**
 * displayError - prints an error message
 * @info: the parameter & return info struct
 * @errorString: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void displayError(info_t *info, char *errorString) 
{
    _eputs(info->fname);
    _eputs(": ");
    printDecimal(info->lineCount, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(errorString);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @inputNumber: the input number
 * @fileDescriptor: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int inputNumber, int fd) 
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO) 
        __putchar = _eputchar;
    if (inputNumber < 0) 
    {
        absoluteValue = -inputNumber;
        __putchar('-');
        count++;
    } 
    else 
        absoluteValue = inputNumber;
    current = absoluteValue;
    for (i = 1000000000; i > 1; i /= 10) 
    {
        if (absoluteValue / i) 
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
   __putchar('0' + current);
    count++;
    
    return (count);
}

/**
 * convertToText - converter function, similar to itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string representation of the number
 */
char *convertToText(long int num, int base, int flags) 
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) 
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do  
    {
        *--ptr = array[n % base];
        n /= base;
    } 
        hile (n != 0);

    if (sign) 
        *--ptr = sign;
    return (ptr);
}

/**
 * eliminateComments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void eliminateComments(char *buf) 
{
    int i;

    for (i = 0; buf[i] != '\0'; i++) 
        if (buf[i] == '#' && (!i || buffer[i - 1] == ' ')) 
        {
            buf[i] = '\0';
            break;
        }
}
