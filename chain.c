#include "shell.h"

/**
 * is_command_chain - checks if the current character in the buffer is a command separator
 * @info: the parameter structure
 * @buf: the character buffer
 * @p: address of the current position in buffer
 *
 * Return: 1 if a command chain, 0 otherwise
 */
int is_command_chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|') 
    {
    buf[j] = 0;
    j++;
    info->command_buffer_type = COMMAND_OR;
    } 
    else if (buf[j] == '&' && buf[j + 1] == '&') 
    {
    buffer[j] = 0;
    j++;
    info->command_buffer_type = COMMAND_AND;
    } 
    else if (buf[j] == ';') { /* found the end of this command */ 
    {
    buf[j] = 0; /* replace semicolon with null */
    info->command_buffer_type = COMMAND_CHAIN;
    } 
    else 
    return (0);
    *p = j;
    return (1);
}

/**
 * check_command_chain - checks whether to continue chaining based on the last status
 * @info: the parameter structure
 * @buf: the character buffer
 * @p: address of the current position in buffer
 * @start_position: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_command_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->command_buffer_type == COMMAND_AND) 
    {
        if (info->status) 
        {
        buf[i] = 0;
        j = len;
        }
    }
    if (info->command_buffer_type == COMMAND_OR) 
    {
        if (!info->status) 
        {
        buf[i] = 0;
        j = len;
        }
    }
    *p = j;
}

/**
 * replace_shell_alias - replaces an alias in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_shell_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++) 
    {
        node = find_node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
        return (0);
        free(info->argv[0]);
        p = findCharacter(node->str, '=');
        if (!p)
        return (0);
        p = duplicateString (p + 1);
        if (!p)
        return (0);
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_variables - replaces variables in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++) 
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        continue;

        if (!stringCompare(info->argv[i], "$?")) 
        {
        replace_string(&(info->argv[i]), duplicate_string(convertToText (info->status, 10, 0)));
        continue;
        }
        if (!stringCompare(info->argv[i], "$$")) 
        {
        replace_string(&(info->argv[i]), duplicate_string(convertToText (get_process_id(), 10, 0)));
        continue;
        }
        node = find_node_starts_with(info->env, &info->argv[i][1], '=');
        if (node) 
        {
        replace_string(&(info->argv[i]), duplicate_string(findCharacter(node->str, '=') + 1));
        continue;
        }
        replace_string(&info->argv[i], duplicate_string(""));
    }
    return (0);
}

/**
 * replace_string - replaces string
 * @old_string: address of the old string
 * @new_string: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_string, char *new_string)
{
free(*old_string);
*old_string = new_string;
return (1);
}
