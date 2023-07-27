#include "main.h"

/**
 * main - main function of the shell.
 * @argc: Number of arguments
 * @argv: array of Values passed.
 * Return: on success returns 0
 */

int main(__attribute((unused)) int argc, __attribute((unused)) char *argv[])
{
	shell_information cmd_data = {NULL};

	signal(SIGINT, signal_handler);

	cmd_data.file_dis = STDIN_FILENO;

	cmd_data.data_name = argv[0];

	if (argv[1] && argc > 1)
	{
		cmd_data.file_dis = open(argv[1], O_RDONLY);
		if (cmd_data.file_dis == -1)
		{
			errno = 127;
			error_msg(argv[0]);
			error_msg(": 0: Can't open ");
			error_msg(argv[1]);
			error_msg("\n");
			exit(errno);
		}
	} else if (isatty(STDIN_FILENO) && argc == 1)
	{
		cmd_data.mode = INTERACTIVE_MODE;
	}

	initializer(&cmd_data);

	nain_loop(&cmd_data);

	return (0);
}
