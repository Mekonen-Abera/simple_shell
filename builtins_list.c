#include "shell.h"

/**
 * builtins_list - A function that searches for match and executes
 * @data: structucture for the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: The function executed if there is a match
 *       : -1 otherwise
 **/
int builtins_list(data_of_program *data)
{
	int counter;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (counter = 0; options[counter].builtin != NULL; counter++)
	{
		if (str_compare(options[counter].builtin, data->command_name, 0))
		{
			return (options[counter].function(data));
		}
	}
	return (-1);
}
