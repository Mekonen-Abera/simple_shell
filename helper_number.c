#include "shell.h"

/**
 * long_to_string - A fuction that converts a number to strings
 * @number: The number converted to a string
 * @string: The buffer save the number as string
 * @base: The base at the number converted
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: Nothing
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}

/**
 * _atoi - It converts a string to an integer
 * @s: A pointer to the origin string
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: int of string
 *       : 0
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - It counts the coincidences of character in a string
 * @string:The pointer to the origin string
 * @character: The string with  characters counted
 * Done by: @Mekonen-Abera & @gebre-a
 * Return: int of string
 *       : 0
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}

