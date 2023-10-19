#include "shell.h"

/**
 * str_length - A function that returns the length of a string
 * @string: The pointer to string
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: length of string
 */
int str_length(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * str_duplicate - It duplicates an string
 * @string: The string copied
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: pointer to the array
 */
char *str_duplicate(char *string)
{
	char *result;
	int length, j;

	if (string == NULL)
		return (NULL);

	length = str_length(string) + 1;

	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (j = 0; j < length ; j++)
	{
		result[j] = string[j];
	}

	return (result);
}

/**
 * str_compare - A function that Compare two strings
 * @string1: The first string or the shorter
 * @string2: The second string or the longer
 * @number: The number of chars compared, 0 if infinite
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: 1 if the strings are equals
 *       : 0 if the strings are different
 */
int str_compare(char *string1, char *string2, int number)
{
	int iterator;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0)
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (iterator = 0; string1[iterator]; iterator++)
		{
			if (string1[iterator] != string2[iterator])
				return (0);
		}
		return (1);
	}
	else
	{
		for (iterator = 0; iterator < number ; iterator++)
		{
			if (string1[iterator] != string2[iterator])
			return (0);
		}
		return (1);
	}
}

/**
 * str_concat - A function that concatenates two strings
 * @string1: The first string to be concatenated
 * @string2: The second string to be concatenated
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: pointer to the array
 */
char *str_concat(char *string1, char *string2)
{
	char *result;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = str_length(string2);

	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; string1[length1] != '\0'; length1++)
		result[length1] = string1[length1];
	free(string1);

	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		result[length1] = string2[length2];
		length1++;
	}

	result[length1] = '\0';
	return (result);
}

/**
 * str_reverse - A function that reverses a string
 * @string: A pointer to string
 * Done by: @MEkonen-Abera & @gebre-a
 * Return: void
 */
void str_reverse(char *string)
{

	int j = 0, length = str_length(string) - 1;
	char hold;

	while (j < length)
	{
		hold = string[j];
		string[j++] = string[length];
		string[length--] = hold;
	}
}
