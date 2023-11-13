#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_shell_alias - unsets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_shell_alias(info_t *info, char *str)
{
    char *p, c;
    int ret;

    p = findCharacter(str, '=');
    if (!p)
    return (1);
    c = *p;
    *p = 0;
    ret = remove_node_at_index(&(info->alias),
       obtain_node_index(info->alias, find_node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_shell_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_shell_alias(info_t *info, char *str)
{
    char *p;

    p = findCharacter(str, '=');
    if (!p)
    return (1);
    if (!*++p)
    return (unset_shell_alias(info, str));

    unset_shell_alias(info, str);
    return ((insert_node_end(&(info->alias), str, 0) == NULL));
}

/**
 * print_shell_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_shell_alias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
    p = findCharacter(node->str, '=');
    for (a = node->str; a <= p; a++)
    _putchar(*a);
    _putchar('\'');
    _puts(p + 1);
    puts("'\n");
    return (0);
    }
    return (1);
}

/**
 * manage_shell_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int manage_shell_alias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
    node = info->alias;
    while (node)
    {
    print_shell_alias(node);
    node = node->next;
    }
    return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
    p = findCharacter(info->argv[i], '=');
    if (p)
    set_shell_alias(info, info->argv[i]);
    else
    print_shell_alias(find_node_starts_with(info->alias, info->argv[i], '='));
    }
    return (0);
}
