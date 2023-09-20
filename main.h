#ifndef _MAIN_H_
#define _MAIN_H_
#include <sys/types.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#define TOK_DELIM " \t\r\n\a"
#define TOK_BUFSIZE 128
#define BUFSIZE 1024
extern char **environ;

/**
 * struct data - Contains all data on runtime.
 * @av: argument vector
 * @input: command line entered from user
 * @args: tokens of command line
 * @status: shell last status
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: shell process ID
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @v: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: Linked list for variables
 */
typedef struct r_var_list
{
	int len_var;
	char *v;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct Line_list_s - single linked list
 * @line: Command line
 * @next: Next node
 * Description: Linked list
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: Linked list for separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

int cd_shell(data_shell *datash);
void cd_to_home(data_shell *datash);
void cd_to(data_shell *datash);
void cd_dot(data_shell *datash);
void cd_previous(data_shell *datash);

char *err_exit_shell(data_shell *datash);
char *err_path_126(data_shell *datash);
char *err_env(data_shell *datash);
char *err_not_found(data_shell *datash);
char *err_get_cd(data_shell *datash);

int repeated_char(char *in, int x);
int err_sep_op(char *in, int x, char lst);
int first_char(char *in, int *x);
void print_syntax_err(data_shell *datash, char *in, int x, int b);
int check_syntax_err(data_shell *datash, char *in);

void aux_hlp(void);
void aux_hlp_general(void);
void aux_hlp_unsetenv(void);
void aux_hlp_env(void);
void aux_hlp_exit(void);

void aux_hlp_setenv(void);
void aux_hlp_alias(void);
void aux_hlp_cd(void);

void free_rvar_list(r_var **hd);
char *aux_itoa(int num);
int get_len(int num);
int _atoi(char *str);

void free_line_list(line_list **hd);
line_list *add_line_node_end(line_list **hd, char *line);
void free_sep_list(sep_list **hd);
r_var *add_rvar_node(r_var **hd, int vr_l, char *v, int vl);
sep_list *add_sep_node_end(sep_list **hd, char sp);

char **_reallocdp(char **p, unsigned int o_size, unsigned int n_size);
void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
void _memcpy(void *n_p, const void *p, unsigned int size);
char *_strcpy(char *dest, char *src);
char *strcat_cd(data_shell *datash, char *masg, char *err, char *ver_str);
/*char *strcat_cd(data_shell *, char *, char *, char *);*/

int _strcmp(char *s1, char *s2);
void rev_string(char *str);
int _strspn(char *s, char *accept);
char *_strchr(char *s, char c);
char *_strcat(char *dest, const char *src);

int _strlen(const char *str);
int _isdigit(const char *str);
char *_strtok(char str[], const char *delim);
int cmp_chars(char str[], const char *delim);
char *_strdup(const char *str);

char *_which(char *cmd, char **_environ);
int is_cdir(char *pth, int *x);
int cmd_exec(data_shell *datash);
int check_err_cmd(char *dir, data_shell *datash);
int is_executable(data_shell *datash);


/*int cmp_env_name(const char *nenv, const char *name);*/
int _env(data_shell *datash);
char *_getenv(const char *name, char **_environ);

int _unsetenv(data_shell *datash);
int _setenv(data_shell *datash);
void set_env(char *name, char *value, data_shell *datash);
char *copy_info(char *name, char *value);

int exec_line(data_shell *datash);
int exit_shell(data_shell *datash);

int get_err(data_shell *datash, int eval);
int get_hlp(data_shell *datash);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

void get_sigint(int sig);
int (*get_builtin(char *cmd))(data_shell *datash);

char *rep_var(char *input, data_shell *datash);
void check_env(r_var **h, char *in, data_shell *data);
char *read_line(int *i_eof);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);

void shell_loop(data_shell *datash);
char *without_comment(char *in);

void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

#endif
