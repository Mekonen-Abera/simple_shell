#include "shell.h"

/**
 * builtin_env - A function that shows the env. the shell runs on
 * @data: structures of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 on sucess
 *       :  other number if declared in the arguments
 */
int builtin_env(data_of_program *data)
{
	int j;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (j = 0; data->tokens[1][j]; j++)
		{
			if (data->tokens[1][j] == '=')
			{
				var_copy = str_duplicate(env_get_key(cpname, data));
				if (var_copy != NULL)
					env_set_key(cpname, data->tokens[1] + j + 1, data);

				print_environ(data);
				if (env_get_key(cpname, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[j] = data->tokens[1][j];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - A function that sets the env. where shell runs
 * @data: structucture of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : other number if declared in the arguments
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - A function that unset the env. datas
 * @data: structures of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : other number if declared in the arguments
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
