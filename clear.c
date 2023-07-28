#include "main.h"

/**
 * clear_aliases - clears allocated memory from alias
 * @var: pointer to head node
 */
void clear_aliases(aliasList *var)
{
	aliasList *alias = var;
	aliasList *buf;

	while (alias != NULL)
	{
		buf = alias;
		alias = alias->move;
		free(temp->data_name);
		free(temp->data_value);
		free(buf);
	}
}

/**
 * be_free - Frees a pointer to a pointer
 * @argu: The memory area to free
 * Return: returns void
 */
void be_free(char **argu)
{
	int i = 0;

	if (!arr)
		return;

	while (argu[s])
	{
		free(argu[s]);
		arr[s] = NULL;
		s++;
	}
	free(argu);
}

/**
 * clear_progdata - function to clear program data
 * @cmd_data: Program data
 * Return: returns void
 */
void clear_progdata(shell_information *cmd_data)
{
	if (cmd_data->args)
		be_free(cmd_data->args);
	else if (cmd_data->command_line)
		free(cmd_data->command_line);
	else if (cmd_data->built_command)
		free(cmd_data->built_command);

	cmd_data->args = NULL;
	cmd_data->command_line = NULL;
	cmd_data->built_command = NULL;
}

/**
 * clear_all - function to free program data
 * @cmd_data: Passed value
 * Return: void
 */
void clear_all(shell_information *cmd_data)
{
	if (cmd_data->command_list && cmd_data->mode == INTERACTIVE_MODE)
	{
		be_free(cmd_data->command_list);
		cmd_data->command_list = NULL;
	}
	if (cmd_data->file_dis != STDIN_FILENO)
	{
		if (close(cmd_data->file_dis))
			perror(cmd_data->data_name);
	}

	if (cmd_data->prog_logic->data)
		be_free(cmd_data->prog_logic->data);

	clear_progdata(cmd_data);
	be_free(environ);
	clear_aliases(cmd_data->alias_data);
}
