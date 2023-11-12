#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

/* for command chaining */
#define CMD_NORMAL	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILENAME	".simple_shell_history"
#define HISTORY_MAXIMUM	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@linecount: the error count
 *@error_number: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@envUpdate: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@command_buffer_type : CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecount;
	int error_number;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envUpdate;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buffer_type ; /* command_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int locate_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* path.c */
int checkIfExecutable(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *findCommandPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* str.funcs.c */
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcat(char *, char *);

/* str.funcs1.c */
char *copyString(char *, char *);
char *duplicateString(const char *);
void _puts(char *);
int _putchar(char);

/* str.funcs2.c */
char *copyStringWithLimit(char *, char *, int);
char *concatenateStringWithLimit(char *, char *, int);
char *findCharacter(char *, char);

/* str.funcs3.c */
char **splitStringByDelim(char *, char *);
char **splitStringByChar(char *, char);

/* mem_funcs.c */
char *_fill_memory(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* mem_funcs1.c */
int bfree(void **);

/* more_funcs.c */
int isInteractiveMode(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int convertToInteger(char *);

/* more_funcs1.c */
int errorToInteger(char *);
void displayError(info_t *, char *);
int printDecimal(int, int);
char *convertToText(long int, int, int);
void eliminateComments(char *);

/* builtin_emulators.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* builtin_emulators1.c */
int display_history(info_t *);
int manage_shell_alias(info_t *);

/* getline.c module */
ssize_t fetch_user_input(info_t *);
int get_line(info_t *, char **, size_t *);
void handle_interrupt(int);

/* info1.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* env1.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *acquire_user_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int create_user_history_list(info_t *info, char *buf, int linecount);
int update_user_history_numbers(info_t *info);

/* liststr.c module */
list_t *insert_node(list_t **, const char *, int);
list_t *insert_node_end(list_t **, const char *, int);
size_t print_list_data(const list_t *);
int remoev_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* liststr2.c module */
size_t count_list(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t obtain_node_index(list_t *, list_t *);

/* chain.c */
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_shell_alias(info_t *);
int replace_variables(info_t *);
int replace_string(char **, char *);

#endif
