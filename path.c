#include "shell.h"

/**
 * checkIfExecutable - checks if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int checkIfExecutable(info_t *info, char *path) 
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st)) 
        return 0;

    if (st.st_mode & S_IFREG) 
    {
        return 1;
    }
    return 0;
}

/**
 * duplicate_chars - duplicates characters from a string
 * @pathString: the PATH string
 * @startIndex: starting index
 * @endIndex: ending index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathString, int startIndex, int endIndex) 
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = startIndex; i < endIndex; i++) 
        if (pathString[i] != ':') 
             buf[k++] = pathString[i];
    buf[k] = 0;
    return (buf);
}

/**
 * findCommandPath - finds this command in the PATH string
 * @info: the info struct
 * @pathString: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *findCommandPath(info_t *info, char *pathString, char *command) 
{
    int i = 0, currentPosition = 0;
    char *path;

    if (!pathString) 
        return NULL;
    if ((stringLength(command) > 2) && startsWith(command, "./")) 
    {
        if (checkIfExecutable(info, command)) 
            return command;
    }
    while (1) 
    {
        if (!pathString[i] || pathString[i] == ':') 
        {
            commandPath = duplicate_chars(pathString, currentPosition, i);
            if (!*path)
                stringConcat(path, command); 
            else 
            {
                stringConcat(path, "/");
                stringConcat(path, command);
            }
            if (checkIfExecutable(info, commandPath)) 
                return commandPath;
            if (!pathString[i]) 
                break;
            currentPosition = i;
        }
        i++;
    }
    return NULL;
}
