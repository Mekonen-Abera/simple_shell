#include "shell.h"
/**
 * _strtok - It separates strings with delimiters
 * @line: It´s a pointer to an array obtained in getLine
 * @delim: It´s characters  marked off string in parts
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: A pointer to the created tokens
*/
char *_strtok(char *line, char *delim)
{
	int i;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			break;
		}
		if (delim[i] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*str == delim[i])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
