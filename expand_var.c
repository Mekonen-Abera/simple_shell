#include "shell.h"

/**
 * expand_variables - A function that expand variables
 * @data: A pointer to a structures of the datas
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing, and sets errno
 */
void expand_variables(data_of_program *data)
{
	int j, k;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (j = 0; line[j]; j++)
		if (line[j] == '#')
			line[j--] = '\0';
		else if (line[j] == '$' && line[j + 1] == '?')
		{
			line[j] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + j + 2);
		}
		else if (line[j] == '$' && line[j + 1] == '$')
		{
			line[j] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + j + 2);
		}
		else if (line[j] == '$' && (line[j + 1] == ' ' || line[j + 1] == '\0'))
			continue;
		else if (line[j] == '$')
		{
			for (k = 1; line[j + k] && line[j + k] != ' '; k++)
				expansion[k - 1] = line[j + k];
			temp = env_get_key(expansion, data);
			line[j] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + j + k);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - A function that expands alias
 * @data: A pointer to the structure of the datas to be programmed
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing, and sets errno
 */
void expand_alias(data_of_program *data)
{
	int j, k, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (j = 0; line[j]; j++)
	{
		for (k = 0; line[j + k] && line[j + k] != ' '; k++)
			expansion[k] = line[j + k];
		expansion[k] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + j + k);
			line[j] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - A function that appends a string at end of buffer
 * @buffer: The buffer filled
 * @str_to_add: A string copied in the buffer
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing, and sets errno
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, j;

	length = str_length(buffer);
	for (j = 0; str_to_add[j]; j++)
	{
		buffer[length + j] = str_to_add[j];
	}
	buffer[length + j] = '\0';
	return (length + j);
}
