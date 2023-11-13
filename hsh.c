#include "shell.h"

/**
 * hsh - main loop for the shell
 * @info: the parameter & return info structure
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t bytes_read = 0;
	int built_in_result = 0;

	while (bytes_read != -1 && built_in_result != -2)
	{
		clear_info(info);
		if (isInteractiveMode(info))
			_puts("$ ");
		        _eputchar(FLUSH_BUFFER);
		read_status = fetch_user_input(info);
		if (bytes_read != -1)
		{
			set_info(info, av);
			built_in_result = locate_builtin(info);
			if (built_in_result == -1)
				find_command(info);
		}
		else if (isInteractiveMode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!isInteractiveMode(info) && info->status)
		exit(info->status);
	if (built_in_result == -2)
	{
		if (info->error_number  == -1)
			exit(info->status);
		exit(info->error_number);
	}
	return (built_in_result);
}

/**
 * locate_builtin - searches for a builtin command
 * @info: the parameter & return info structure
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locate_builtin(info_t *info)
{
	int i, built_in_result = -1;
	builtin_commands builtintbl[] = {
		{"exit", my_exit},
		{"env", _myenv},
		{"help", my_help},
		{"history", display_history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", my_cd},
		{"alias",  manage_shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintb[i].type; i++)
		if (stringCompare(info->argv[0], builtintb[i].type) == 0)
		{
			info->linecount++;
			built_in_result = built_in_table[i].func(info);
			break;
	}
	return (built_in_result);
}

/**
 * find_command - searches for a command in the PATH
 * @info: the parameter & return info structure
 *
 * Return: void
 */
void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->linecount++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findCommandPath(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((isInteractiveMode(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && checkIfExecutable(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			displayError(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks an execution thread to run the command
 * @info: the parameter & return info structure
 *
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: ADD ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv,get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: ADD ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				displayError(info, "Permission denied\n");
		}
	}
}
