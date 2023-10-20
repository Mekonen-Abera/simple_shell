#include "shell.h"

/**
 * print_alias - A function that shows aliases
 * @data: structure of datas to be programmed
 * @alias: The name of alias printed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       :  other number if declared in arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - A function that adds aliases
 * @data: A structures of datas to be programmed
 * @name: The name of the alias requested
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       :  other number if declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	return (NULL);
}

/**
 * set_alias - A function that override aliases
 * @alias_string: set alias in the form (name='value')
 * @data: structucture of the datas programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       :  other number if declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
	{	
		data->alias_list[j] = str_duplicate(alias_string);
	}
	return (0);
}

