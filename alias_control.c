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
	int j, k, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (j = 0; data->alias_list[j]; j++)
		{
			if (!alias || (str_compare(data->alias_list[j], alias, alias_length)
				&&	data->alias_list[j][alias_length] == '='))
			{
				for (k = 0; data->alias_list[j][k]; k++)
				{
					buffer[k] = data->alias_list[j][k];
					if (data->alias_list[j][k] == '=')
						break;
				}
				buffer[k + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[j] + k + 1);
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
	int j, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(name, data->alias_list[j], alias_length) &&
			data->alias_list[j][alias_length] == '=')
		{
			return (data->alias_list[j] + alias_length + 1);
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
	int j, k;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (j = 0; alias_string[j]; j++)
		if (alias_string[j] != '=')
			buffer[j] = alias_string[j];
		else
		{
			temp = get_alias(data, alias_string + j + 1);
			break;
		}

	for (k = 0; data->alias_list[k]; k++)
		if (str_compare(buffer, data->alias_list[k], j) &&
			data->alias_list[k][j] == '=')
		{
			free(data->alias_list[k]);
			break;
		}

	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[k] = str_duplicate(buffer);
	}
	else
	{
		data->alias_list[k] = str_duplicate(alias_string);
	}
	return (0);
}
