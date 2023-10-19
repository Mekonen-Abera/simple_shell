#include "shell.h"

/**
* _getline - A function that reads one line from the prompt
* @data: structure for the data to be programmed
* Done by: @Mekonen-Abera & @gebre-a
* Return:The reading counting bytes
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, j = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (j = 0; array_commands[j]; j++)
		{
			free(array_commands[j]);
			array_commands[j] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		j = 0;
		do {
			array_commands[j] = str_duplicate(_strtok(j ? NULL : buff, "\n;"));
			j = check_logic_ops(array_commands, j, array_operators);
		} while (array_commands[j++]);
	}

	data->input_line = array_commands[0];
	for (j = 0; array_commands[j]; j++)
	{
		array_commands[j] = array_commands[j + 1];
		array_operators[j] = array_operators[j + 1];
	}

	return (str_length(data->input_line));
}

/**
* check_logic_ops - A function that checks and split for && and || operators
* @array_commands: An array of commands
* @j: index in an array_commands checked
* @array_operators: An array of the logical operators
* Done by: @Meonen-Abera & @gebre-a
* Return: The index of the last command in an array_commands
*/
int check_logic_ops(char *array_commands[], int j, char array_operators[])
{
	char *temp = NULL;
	int k;

	for (j = 0; array_commands[j] != NULL  && array_commands[j][k]; k++)
	{
		if (array_commands[j][k] == '&' && array_commands[j][k + 1] == '&')
		{
			temp = array_commands[j];
			array_commands[j][k] = '\0';
			array_commands[j] = str_duplicate(array_commands[j]);
			array_commands[j + 1] = str_duplicate(temp + k + 2);
			j++;
			array_operators[j] = '&';
			free(temp);
			k = 0;
		}
		if (array_commands[j][k] == '|' && array_commands[j][k + 1] == '|')
		{
			temp = array_commands[j];
			array_commands[j][k] = '\0';
			array_commands[j] = str_duplicate(array_commands[j]);
			array_commands[j + 1] = str_duplicate(temp + k + 2);
			j++;
			array_operators[j] = '|';
			free(temp);
			k = 0;
		}
	}
	return (j);
}
