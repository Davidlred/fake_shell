#include "main.h"

/**
 * set_environment - sets an environment
 * @variable: environment variable
 * @value: value of the variable
 * Return: 0 if successful, otherwise, -1
 */
int set_environment(char *variable, char *value)
{
	char *env;
	int i;
	int length;

	if (variable == NULL || value == NULL)
	{
		perror("Invalid argument\n");
		return (0);
	}

	length = str_len(variable);
	env = malloc(length + str_len(value) + 2);
	if (env == NULL)
	{
		perror("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	str_copy(env, variable);
	str_coc(env, "=");
	str_coc(env, value);

	for (i = 0; environ[i]; i++)
	{
		if (strn_cmp(environ[i], variable, length) == 0 && environ[i][length] == '=')
		{
			free(environ[i]);
			environ[i] = env;
			return (0);
		}
	}
	free(environ[i]);
	environ[i] = env;
	environ[i + 1] = NULL;
	return (0);
}
/**
 * un_set_environment - clears environment variable
 * @variable: name of variable
 * Return: 0 on success, else -1
 */
int un_set_environment(char *variable)
{
	char *environment;
	int len;
	int i;
	int index = 0;

	if (variable == NULL)
		return (0);

	environment = get_environment(variable);
	if (environment == NULL)
	{
		perror("cannot find variable\n");
		return (0);
	}

	len = str_len(variable);

	for (i = 0; environ[i]; i++)
	{
		if (index == NULL)
		{
			if (strn_cmp(environ[i], var, len) == 0 && environ[i][len] == '=')
			{
				free(environ[i]);
				index = 1;
			}
			continue;
		}
		environ[i - 1] = environ[i];
	}
	environ[i - 1] = NULL;
	return (0);
}
/**
 * checker - checks a file
 * @args: passed value
 * Return: void
 */

int checker(char *args)
{
	struct stat fileStatus;

	if (stat(args, &fileStatus) == 0)
	{

		if (access(args, X_OK) || S_ISDIR(fileStatus.st_mode))
		{
			errno = 126;
			return (COMMAND_ERROR);
		}
		return (1);
	}
	errno = 127;
	return (COMMAND_ERROR);
}
/**
 * builder_list - Builds the command
 * @cmd_data:  data
 * Return: void
 */
void builder_list(shell_information *cmd_data)
{
	char **up;
	char *down;
	int i = 0;
	char *input_string = i ? NULL : cmd_data->command_line;

	up = malloc(MAX_TOKENS * sizeof(char *));
	if (up == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	while ((down = str_dup(str_tok(input_string, ";"))))
	{
		up[i++] = down;
		input_string = NULL;
	}

	up[i] = NULL;
	cmd_data->command_list = up;
}

/**
 * if_checker - Checks if a comment exist
 * @cmd_data:  data
 * Return: 1 if comment else 0
 */
int if_checker(shell_information *cmd_data)
{
	int i;

	for (i = 0; cmd_data->runing_cmd[i]; i++)
	{
		if (cmd_data->runing_cmd[i] == '#')
		{
			if (i == 0)
			{
				cmd_data->runing_cmd = str_dup("");
				return (1);
			}

			if (cmd_data->runing_cmd[i - 1] == ' ')
			{
				cmd_data->runing_cmd = str_tok(cmd_data->runing_cmd, "#");
				return (1);
			}
		}
	}
	return (0);
}
