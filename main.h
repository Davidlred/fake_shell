#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

#define MAX_BUFFER 64
#define MAX_TOKEN_SIZE 32
#define MAX_LENGTH 4096
#define BUF_SIZE 1024
#define DELIMETER " \n"

#define PROMPTER "$ "
#define NOT_BUILTIN -99 
#define COMMAND_ERROR -1

#define INTERACTIVE_MODE 99

#define BUILTIN_CD "cd"
#define BUILTIN_ENV "env"
#define BUILTIN_EXIT "exit"
#define BUILTIN_SETENV "setenv"
#define BUILTIN_UNSETENV "unsetenv"
#define BUILTIN_ALIAS "alias"

#define LOGICAL_OR 1
#define LOGICAL_AND 2
extern char **environ;
extern int errno;

typedef struct alias_data
{
	char *data_name;
	char *data_value;
	struct alias_data *move;
} aliasList;

typedef struct operation_data
{
	char **data;
	int int_data[MAX_BUFFER];
} operators;


typedef struct program_data
{
	char *program_name;
	int tracker;
	char *runing_cmd;
	char **args;
	char *command_line;
	char **command_list;
	char command_line_buffer[MAX_LENGTH];
	operators *prog_logic;
	aliasList *alias_data;
	int file_dis;
	int mode;

} shell_information;

typedef struct built_function
{
	char *built_command;
	int (*action)(shell_information *cmd_data);
} inbuilt_action;

int _digit(char *i);
char *str_coc(char *destination, const char *source);
char *str_copy(char *dest, const char *src);
size_t str_len(const char *string);
int strn_cmp(const char *n1, const char *n2, size_t s);
char *str_dup(const char *string);
int str_cmp(char *n1, char *n2);
char *str_tok(char *str, char *delim);
char *dup_range(char *source, int old, int now);
char *trim_str(char *string);



void be_free(char **argu);
void clear_progdata(shell_information *cmd_data);
void clear_all(shell_information cmd_data);
void clear_aliases(aliasList *var);

ssize_t read_line(shell_information *cmd_data);
void pop_up(shell_information *cmd_data);
void input_tok(shell_information *cmd_data);
char *path_handler(char *args);
int checker(char *args);
int exec(shell_information *cmd_data);
void main_loop(shell_information *cmd_data);
int if_built(shell_information *cmd_data);
void initializer(shell_information *cmd_data);
void builder_list(shell_information *cmd_data);
int if_checker(shell_information *cmd_data);
operators *exp_ops(char *runing_cmd, operators *cmd_data);
char *var_exp(char *line, shell_information *cmd_data);
char *get_environment(const char *data_name);
int set_environment(char *variable, char *value);
int un_set_environment(char *variable);

int env_printer(shell_information *cmd_data);
int exit_in(shell_information *cmd_data);
int setenv_forbuilt(shell_information *cmd_data);
int unset_built(shell_information *cmd_data);
int enter_built(shell_information *cmd_data);
int build_aly(shell_information *cmd_data);

void alias_adder(char *data_name, char *data_value, shell_information *cmd_data);
void alias_printer(shell_information *cmd_data, char *names);
aliasList *alias_getter(shell_information *cmd_data, char *data_name);

void show_error(shell_information *cmd_data);
ssize_t error_msg(char *err);

void stringconvert(char *buf, int number);
void str_reverse(char *string);
int digitconvert(char *string);
void signal_handler(int signal);

#endif
