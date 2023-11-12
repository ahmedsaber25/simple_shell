#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed as an error
 *
 * Return: Nothing
 */
void _eputs(char *str) 
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0') 
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print 
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int _eputchar(char c) 
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == FLUSH_BUFFER || buf >= WRITE_BUFFER_SIZE) 
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != FLUSH_BUFFER)
        buf[i++] = c;
    return (1);
}

/**
 * _putfd - writes the character to  given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success, returns 1.
 * On error, returns -1, and sets errno appropriately.
 */
int _putfd(char c, int fd) 
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == FLUSH_BUFFER || buf >= WRITE_BUFFER_SIZE) 
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != FLUSH_BUFFER)
        buf[i++] = c;
    return 1;
}

/**
 * _putsfd - prints an input string 
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putsfd(char *str, int fd) 
{
    int i = 0;

    if (!str)
        return 0;

    while (*str) {
        i += _putfd(*str++, fd);
    }
    return i;
}
