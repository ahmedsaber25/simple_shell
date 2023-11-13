#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info) 
{
    int exit_status;

    if (info->argv[1])   /* If there is an exit arguement */
    {
        exit_status = errorToInteger (info->argv[1]);
        if (exit_status == -1)
	{
            info->status = 2;
           displayError(info, "Illegal number: ");
            _eputs(info->argv[1]);
	    _eputchar('\n');
            return (1);
        }
        info->error_number = errorToInteger (info->argv[1]);
        return -(2);
    }
    info->error_number = -1;
    return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int my_cd(info_t *info)
{
    char *string, *directory, buffer[1024];
    int chdir_return;

    string = getcwd(buffer, 1024);
    if (!string) 
    {
        _puts("TODO: >>getcwd failure emsg here<<\n");
    }
    if (!info->argv[1]) 
    {
        dir = _getenv(info, "HOME=");
        if (!directory)
            chdir_return = /* TODO: what should this be? */
                chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
        else
            chdir_return = chdir(directory);
    } 
    else if (stringCompare(info->argv[1], "-") == 0) 
    {
        if (!_getenv(info, "OLDPWD="))
	{
            _puts(current_directory);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_return = /* TODO: what should this be? */
            chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
    } else {
        chdir_return = chdir(info->argv[1]);
    }
    if (chdir_return == -1)
    {
        displayError(info, "can't cd to ");
        _eputs(info->argv[1]);
	_eputchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int my_help(info_t *info)
{
    char **argument_array;

    argument_array = info->argv;
   _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*argument_array); /* temporary unused workaround */
    return (0);
}
