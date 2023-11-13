#include "shell.h"

/**
 * receive_user_input_buffer - buffers concatenated commands from user input
 * @info: structure containing input parameters
 * @buf: address of buffer
 * @len: address of length variable
 *
 * Return: number of bytes read
 */
ssize_t receive_user_input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t length_position = 0;

	if (!*len)/* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_interrupt);
#if USE_GETLINE
		bytes_read = getline(buf, &length_position, stdin);
#else
		bytes_read = get_line(info, buf, &length_position);
#endif
if (bytes_read > 0) 
{
  if ((*buf)[bytes_read - 1] == '\n') 
  {
    (*buf)[bytes_read - 1] = '\0'; /* remove trailing newline */
    bytes_read--;
  }
  info->linecount_flag = 1;
  eliminateComments(*buf);
  create_user_history_list(info, *buf, info->histcount++);
  /* if (findCharacter(*buf, ';')) is this a command chain? */
  {
       *len = bytes_read;
     info->cmd_buf = buf;
  }
}
}
    return (bytes_read);
}

/**
 * fetch_user_input - retrieves a line without the newline character
 * @info: structure containing input parameters
 *
 * Return: number of bytes read
 */
ssize_t fetch_user_input(info_t *info)
{
	static char *buf;    /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(FLUSH_BUFFER);
	bytes_read = receive_user_input_buffer(info, &buf, &len);
	if (bytes_read == -1)
		return (-1);
	if (len)       /* we have commands left in the chain buffer */
	{
		j = i;  /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_command_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_command_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len)  /* reached end of buffer? */
		{
			i = len = 0;
			info->command_buffer_type = CMD_NORMAL;
		}

		*buf_p = p;
		return (stringLength(p));
	}

	*buf_p = buf;       /* else not a chain, pass back buffer from  get_line() */
	return (bytes_read);  /* return length of buffer from  get_line() */
}

/**
 * read_buffer - reads a buffer
 * @info: structure containing input parameters
 * @buf: buffer
 * @i: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->read_fd, buf, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * get_line - fetches the next line of input from STDIN
 * @info: structure containing input parameters
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, string = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		string = *length;
	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(info, buf, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = findCharacter(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, string, string ? string + k : k + 1);
	if (!new_p)   /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		concatenateStringWithLimit(new_p, buf + i, k - i);
	else
		copyStringWithLimit(new_p, buf + i, k - i + 1);

	string += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = string;
	*ptr = p;
	return (string);
}

/**
 * handle_interrupt - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_interrupt(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
