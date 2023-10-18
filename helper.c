#include "shell.h"

/**
 * free_recurrent_data - A function that frees the fields in the loop
 * @data: structure of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - A function that frees all fields of the data
 * @data: structure of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - A function that frees each pointer of an array of pointers
 * @array: An arrays of pointers
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing
 */
void free_array_of_pointers(char **array)
{
	int j;

	if (array != NULL)
	{
		for (j = 0; array[j]; j++)
			free(array[j]);

		free(array);
		array = NULL;
	}
}
