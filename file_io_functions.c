#include "shell.h"

/**
 * acquire_user_history_file - retrieves the user's history file
 * @info: parameter struct
 *
 * Return: allocated string containing user's history file path
 */
char *acquire_user_history_file(info_t *info)
{
    char *buf, *directory;

    directory = _getenv(info, "HOME=");
    if (!directory)
    return (NULL);
    buf = malloc(sizeof(char) * (stringLength(directory) + stringLength(HISTORY_FILENAME) + 2));
    if (!buf)
    return (NULL);
    buf[0] = 0;
   copyString(buf, directory);
    stringConcat(buf, "/");
    stringConcat(buf, HISTORY_FILENAME);
    return (buf);
}

/**
 * write_history - creates or appends to the user's history file
 * @info: the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_history (info_t *info)
{
    ssize_t fd;
    char *file_name = acquire_user_history_file(info);
    list_t *node = NULL;

    if (!file_name)
    return (-1);

    fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);
    if (fd == -1)
    return (-1);
    for (node = info->user_history; node; node = node->next)
    {
    _putsfd(node->str, fd);
    _putfd('\n', fd);
    }
    _putfd(FLUSH_BUFFER, fd);
    close(fd);
    return (1);
}

/**
 * read_history - reads user's history from the history file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 on failure
 */
int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd,  rdlen, file_size = 0;
    struct stat st;
    char *buf = NULL, *file_name = acquire_user_history_file(info);

    if (!file_name)
    return (0);

    fd = open(file_name, O_RDONLY);
    free(file_name);
    if (fd == -1)
    return (0);
    if (!fstat(fd, &st))
    file_size = st.st_size;
    if (file_size < 2)
    return (0);
    buffer = malloc(sizeof(char) * (file_size + 1));
    if (!buf)
    return (0);
     rdlen = read(fd, buf, file_size);
    buf[file_size] = 0;
    if (rdlen <= 0)
    return (free(buf), 0);
    close(fd);
    for (i = 0; i < file_size; i++)
    if (buf[i] == '\n')
    {
    buf[i] = 0;
    create_user_history_list(info, buf + last, linecount++);
    last = i + 1;
    }
    if (last != i)
    create_user_history_list(info, buf + last, linecount++);
    free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= HISTORY_MAXIMUM)
    remove_node_at_index(&(info->user_history), 0);
    update_user_history_numbers(info);
    return (info->histcount);
}

/**
 * create_user_history_list - adds an entry to a user's history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer containing the history entry
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int create_user_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->user_history)
    node = info->user_history;
    insert_node_end(&node, buf, linecount);
    if (!info->user_history)
    info->user_history = node;
    return (0);
}

/**
 * update_user_history_numbers - renumbers the user's history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int update_user_history_numbers(info_t *info)
{
    list_t *node = info->user_history;
    int i = 0;

    while (node)
    {
    node->num = i++;
    node = node->next;
    }
    return (info->histcount = i);
}
