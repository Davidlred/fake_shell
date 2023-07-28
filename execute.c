#include "main.h"

/**
 * path_handler - looks for executable commands in path
 * @args: command name
 * Return: path to the command
 */
char *path_handler(char *args)
{
	char *pathway = str_dup(get_environment("PATH"));

	char *directory = str_tok(pathway, ":");

	char *command_path;
	size_t len;
	size_t len_of_agrs;
	size_t len_of_path;

	while (directory != NULL)
	{
		len = _strlen(dir);
		len_of_args = str_len(args);
		len_of_path = (len + len_of_args) + 2;

		command_path = malloc(len_of_path);
		if (command_path == NULL)
		{
			perror("ish: allocation error");
			exit(EXIT_FAILURE);
		}
		str_cpy(command_path, directory);
		str_coc(command_path, "/");
		str_coc(command_path, args);

		if (access(command_path, F_OK) == 0)
		{
			free(pathway);
			return (command_path);
		}
		free(command_path);
		directory = str_tok(NULL, ":");
	}
	free(pathway);
	return (NULL);
}

/**
 * execute - execution handler
 * @cmd_data: data contained within the program
 * Return: returns void
 */
void execute(shell_information *cmd_data)
{
	pid_t pid1;
	int status;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror(cmd_data->program_name);
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0)
	{
		if (execve(cmd_data->args[0], cmd_data->args, environ) == -1)
			perror(cmd_data->program_name);
		exit(errno);
	} else
	{
		waitpid(pid1, &status, WUNTRACED);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}
}

/**
 * exec - external handlers
 * @cmd_data: data contained in the program
 * Return: error code
 */
int exec(shell_information *cmd_data)
{
	char *commannd_path = cmd_data->args[0];
	int container;

	if (!(command_path[0] == '/' || command_path[0] == '.'))
	{
		command_path = path_handler(command_path);
		if (command_path == NULL)
		{
			errno = 127;
			return (COMMAND_ERROR);
		}
		free(cmd_data->args[0]);
		cmd_data->args[0] = command_path;
	}

	container = checker(command_path);


	if (container == 1)
	{
		execute(cmd_data);
		return (EXIT_SUCCESS);
	}
	return (container);
}
