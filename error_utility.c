#include "main.h"

/**
 * error_msg - Prints an error message
 * @err: error message
 * Return: length of message
 */
ssize_t error_msg(char *err)
{
	return (write(STDERR_FILENO, err, str_len(err)));
}

/**
 * error_head - Prints the error head
 * @cmd_data: program data
 * Return: return void
 */
void error_head(shell_information *cmd_data)
{
	char sharon[20] = {'\0'};

	number_to_string(sharon, cmd_data->tracker);
	error_msg(cmd_data->data_name);
	error_msg(": ");
	error_msg(sharon);
	error_msg(": ");
	error_msg(cmd_data->args[0]);
	error_msg(": ");
}

/**
 * show_error - Handles error showing
 * @cmd_data: Program data
 * Return: returns void
 */
void show_error(shell_information *cmd_data)
{
	if (str_cmp(cmd_data->args[0], BUILTIN_ALIAS))
		error_head(cmd_data);
	if (errno == 126 || errno == 127)
	{
		if (erro == 127)
			error_msg("not found\n");
		else
			error_msg("Permission not given\n");
	}

	if (str_cmp(cmd_data->args[0], BUILTIN_CD) == 0)
	{
		error_msg("can not cd to ");
		error_msg(data->args[1]);
		error_msg("\n");
	}

	if (_strcmp(data->args[0], BUILTIN_EXIT) == 0)
	{
		error_msg("Illegal number: ");
		error_msg(cmd_data->args[1]);
		erroe_msg("\n");
	}
}
