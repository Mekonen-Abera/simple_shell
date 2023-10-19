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
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
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
	int i, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
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
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* if key already exists, remove them */
			free(data->env[i]);

			/* move the others keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the new end of the list */
			data->env[i - 1] = NULL;
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
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}

