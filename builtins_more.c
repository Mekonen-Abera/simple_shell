#include "shell.h"

/**
 * builtin_exit - A function that exit the status of the program
 * @data: structuctures of the data to be programmed
 * Return: 0 on sucess
 *       : other number if declared in the arguments
 */
int builtin_exit(data_of_program *data)
{
	int j;

	if (data->tokens[1] != NULL)
	{
		for (j = 0; data->tokens[1][j]; j++)
			if ((data->tokens[1][j] < '0' || data->tokens[1][j] > '9')
				&& data->tokens[1][j] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - A function that change the current directory
 * @data: structucture of the data to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : other number if declared in the arguments
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - A function that sets the work directory
 * @data: structucture of the data programmed
 * @new_dir:The path to be set as work directory
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 if sucess
 *       : other number if declared in the arguments
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - It shows the envi. shell runs on
 * @data: structuctures of the data to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : other number if declared in the arguments
 */
int builtin_help(data_of_program *data)
{
	int j, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (j = 0; mensajes[j]; j++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[j], length))
		{
			_print(mensajes[j] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - A builtin function shows aliases
 * @data: structucture for the data to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : other number if declared in the arguments
 */
int builtin_alias(data_of_program *data)
{
	int j = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++j])
	{
		if (count_characters(data->tokens[j], "="))
			set_alias(data->tokens[j], data);
		else
			print_alias(data, data->tokens[j]);
	}

	return (0);
}