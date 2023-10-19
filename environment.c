#include "shell.h"

/**
 * env_get_key - A function that gets values of an envi. variable
 * @key: The variables environment
 * @data: structures of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: A pointer to the value of the variable
 *       : NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int j, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (j = 0; data->env[j]; j++)
	{
		if (str_compare(key, data->env[j], key_length) &&
		 data->env[j][key_length] == '=')
		{
			return (data->env[j] + key_length + 1);
		}
	}
	return (NULL);
}
/**
 * env_set_key - A function that overwrite the value of the environment
 * @key: The name of the variable to be set
 * @value: The new values to be setted
 * @data: structures of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 for sucess
 *       : 1 for the parameters are NULL or, 2 for there is an erroror
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int j, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (j = 0; data->env[j]; j++)
	{
		if (str_compare(key, data->env[j], key_length) &&
		 data->env[j][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[j]);
			break;
		}
	}
	data->env[j] = str_concat(str_duplicate(key), "=");
	data->env[j] = str_concat(data->env[j], value);

	if (is_new_key)
	{
		data->env[j + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - A function that removes a key from the environment
 * @key: The key to remove from the environment
 * @data: The sructure of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 1 if the key was removed
 *       : 0 if the key does not exist
 */
int env_remove_key(char *key, data_of_program *data)
{
	int j, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (j = 0; data->env[j]; j++)
	{
		if (str_compare(key, data->env[j], key_length) &&
		 data->env[j][key_length] == '=')
		{
			free(data->env[j]);

			j++;
			for (; data->env[j]; j++)
			{
				data->env[j - 1] = data->env[j];
			}
			data->env[j - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - A function that prints the current environment
 * @data: structures for datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing
 */
void print_environ(data_of_program *data)
{
	int i;

	for (i = 0; data->env[i]; i++)
	{
		_print(data->env[i]);
		_print("\n");
	}
}
