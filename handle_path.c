#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - A function that finds a program in a path
 * @data: A pointer to the datas to be programmed
 * Done by: @Mekonen-Abera & gebre-a
 * Return: 0 for success
 *       :  errcode otherwise
 */

int find_program(data_of_program *data)
{
	int j = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (j = 0; directories[j]; j++)
	{
		directories[j] = str_concat(directories[j], data->tokens[0]);
		ret_code = check_file(directories[j]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[j]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - A function that tokenize the path in the directory
 * @data: A pointer to the data programs
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: The array of the path directories
 */

char **tokenize_path(data_of_program *data)
{
	int j = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (j = 0; PATH[j]; j++)
	{
		if (PATH[j] == ':')
			counter_directories++;
	}

	tokens = malloc(sizeof(char *) * counter_directories);
	j = 0;
	tokens[j] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[j++])
	{
		tokens[j] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - A function that checks if a file is exists
 * and if it has excecution permisions
 * @full_path: A pointer to the full file name
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: 0 on success
 *       :  error code if it exists
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
