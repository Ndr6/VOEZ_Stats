/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** Made by Ndr
*/

#include <unistd.h>

int my_putstr(char const *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		write (1, &str[i], 1);
	return 0;
}
