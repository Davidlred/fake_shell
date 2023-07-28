#include "main.h"

/**
 * initializer - starts the program data
 * @cmd_data:  data
 * Return: void
 */
void initializer(shell_information *cmd_data)
{
	operators prog_logic = {NULL};
	char **environment;
	char *var;
	int i = 0;

	environment = malloc(64 * sizeof(char *));
	if (environment == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while (environ[i])
	{
		var = _strdup(environ[i]);
		env[i] = var;
		i++;
	}

	environment[i] = NULL;
	environ = environment;

	cmd_data->runing_cmd = NULL;
	cmd_data->command_line = NULL;
	cmd_data->tracker = 0;
	cmd_data->args = NULL;
	cmd_data->command_list = NULL;
	cmd_data->alias_data = NULL;
	cmd_data->prog_logic = &prog_logic;
}

/**
 * if_built - Checks if the command is in built
 * @cmd_data:  data
 * Return: sucess
 */
int if_built(shell_information *cmd_data)
{
	int i = 0;
	in_built_action actions[] = {
		{BUILTIN_EXIT, exit_in},
		{BUILTIN_CD, enter_built},
		{BUILTIN_ENV, env_printer},
		{BUILTIN_SETENV, setenv_forbuilt},
		{BUILTIN_UNSETENV, unset_built},
		{BUILTIN_ALIAS, build_aly},
		{NULL, NULL}};

	while (actions[i].built_command)
	{
		if (str_cmp(cmd_data->args[0], actions[i].built_command) == 0)
			return (actions[i].action(cmd_data));
		i++;
	}

	return (FAKE);
}

/**
 * get_environment - Gets the environment
 * @data_name: The name of the environment
 * Return: environment variable
 */
char *get_environment(const char *data_name)
{
	size_t len = str_len(data_name);

	char *val;
	int i = 0;

	while (environ[i] != NULL)
	{
		if (strn_cmp(environ[i], data_name, len) == 0 && environ[i][len] == '=')
		{
			val = &environ[i][len + 1];
			return (val);
		}
		i++;
	}
	return (NULL);
}

