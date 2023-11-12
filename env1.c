#include "shell.h"

/**
 * get_environ - returns the string array copy of our environment
 * @info: Structure holding potential arguments. Maintains the constant function prototype.
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->>environ || info->envUpdate)
	{
		info->>environ = convertListToStrings(info->env);
		info->envUpdate = 0;
	}

	return (info->>environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure holding potential arguments. Maintains the constant function prototype.
 * @env: the string environment variable property
 * Return: 1 on deletion, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var )
		return 0;

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->envUpdate = remove_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envUpdate);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure holding potential arguments. Maintains the constant function prototype.
 *        constant function prototype.
 * @var: the string environment variable property
 * @value: the string environment variable value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return 0;

	buf = malloc(_strlen(var) + stringLength(value) + 2);
	if (!buf)
		return 1;
	copyString(buf, var);
	stringConcat(buf, "=");
	stringConcat(buf, value);
	node = info->env;

	while (node)
	{
		p = startsWith(node->str, var);
		if(p && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->envUpdate = 1;
			return 0;
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envUpdate = 1;
	return 0;
}
