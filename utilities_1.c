#include "main.h"

/**
 * exp_ops - Expands the operand
 * @built_command: A command
 * @cmd_data: The data
 * Return: The ops data
 */
operators *exp_ops(char *built_command, operators *cmd_data)
{
	char *dup = str_dup(built_command);
	int len = str_len(dup);

	int start = 0;

	int index = 0;

	int old_index = 0;

	cmd_data->operands = calloc(MAX_TOKENS, sizeof(char *));
	if (!cmd_data->operands)
	{
		perror(" Memory allocation error");
		exit(EXIT_FAILURE);
	}

	for (; dup[index]; index++)
	{
		if (strn_cmp(dup + index, "||", 2) == 0 || strn_cmp(dup + index, "&&", 2) == 0)
		{
			cmd_data->operands[old_index] = dup_range(built_command, start, index);
			if (dup[index] == '|')
			{
				cmd_data->operators[old_index] = LOGICAL_OR;
			} else
			{
				cmd_data->operators[old_index] = LOGICAL_AND;
			}
			old_index++;

			start = index + 2;
			index = start - 1;
		}
	}

	cmd_data->operands[old_index] = dup_range(built_command, start, index);
	free(dup);
	return (cmd_data);
}

/**
 * var_exp - Expands command line varibles
 * @line: The command line
 * @cmd_data: The Program data
 * Return: The expanded line
 */
char *var_exp(char *line, shell_information *cmd_data)
{
	char num[10] = {'\0'};
	char *alias;

	char var_buf[MAX_BUFFER] = {'\0'};

	int cern = 0;

	int nern = 0;

	int i;
	int j;
	int found;
	if (line == NULL)
		return (NULL);
	while (*line)
	{
		if (*line == '$' && !(*(line + 1) == ' ' || *(line + 1) == '\0'))
		{
			if (((*(line + 1) == '$') || *(line + 1) == '?'))
			{
				string_convert(num, *(line + 1) == '$' ? getpid() : errno);
				for (i = 0; num[i]; i++, cern++)
					cmd_data->command_line_buffer[cern] = num[i];
				line = line + 2;

				nern = nern + 2;
				continue;
			}
			found = 0;
			for (i = 1; *(line + i) && *(line + i) != ' ' && *(line + i) != '$'; i++)
			{
				var_buf[i - 1] = *(line + i);

				var_buf[i] = '\0';

				alias = get_environment(var_buf);
				if (alias)
				{
					found = 1;
					for (j = 0; alias[j]; j++, cern++)
						cmd_data->command_line_buffer[cern] = alias[j];
					break;
				}
			}
			if (found)
			{
				line = line + i + 1;
				nern = nern + i + 1;
			} else
			{
				line = line + i;
				nern = nern + i;
			}
			continue;
		}
		cmd_data->command_line_buffer[cern++] = *line;
		nern++;
		line++;
	}
	cmd_data->command_line_buffer[cern] = '\0';
	free(line - nern);
	return (str_dup(cmd_data->command_line_buffer));
}

/**
 * expander - Expands aliases
 * @string: line of command
 * @cmd_data: Program dat
 * @snake: check for resurviness
 * Return: an expanded line
 */
char *expander(char *string, int snake, shell_information *cmd_data)
{
	char line[4028] = {'\0'};

	char buf[64] = {'\0'};
	aliasList *alias;

	int i = 0;

	int index = 0;

	int j = 0;

	while (*string)
	{
		if (*string == ' ')
		{
			buf[i] = '\0';
			alias = alias_getter(cmd_data, buf);

			if (alias)
			{
				index = index - i;

				line[index] = '\0';
				if (snake)
				{
					char *expanded_value = expander(alias->data_value, 0, cmd_data);

					str_coc(line, expanded_value);
					free(expanded_value);
				} else
				{
					str_coc(line, alias->data_value);
				}

				index = index + str_len(alias->data_value);
			}
			i = 0;
			while (*string && *string == ' ')
			{
				line[index++] = *(string++);
				j++;
			}
			line[index] = '\0';
			continue;
		}

		buf[i] = *string;
		line[index] = *string;
		string++;
		i++;
		index++;
		j++;
	}
	buf[i] = '\0', alias = alias_getter(cmd_data, buf);
	if (alias)
	{
		index = index - i;
		line[index] = '\0';
		if (snake)
		{
			char *value2 = expander(alias->data_value, 0, cmd_data);

			str_coc(line, value2);
			free(value2);
		} else
		{
			str_coc(line, alias->data_value);
		}
		index = index + str_len(alias->data_value);
	}
	free(string - j);
	return (str_dup(line));
}
