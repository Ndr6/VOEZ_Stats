/*
** EPITECH PROJECT, 2018
** GNL
** File description:
** By Ndr
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char *my_strcat(char *src, char *src2)
{
	int lsrc;
	int lsrc2;
	char *dest;
	int i;

	for (lsrc = 0; src[lsrc] != '\0'; lsrc++){}
	for (lsrc2 = 0; src2[lsrc2] != '\0'; lsrc2++){}
	dest = dest = malloc(sizeof(char) * (lsrc + lsrc2) + 1);
	if (dest == NULL)
		return NULL;
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	if (lsrc > 0)
		free(src);
	for (int j = 0; src2[j] != '\0' && src2[j] != '\n'; i++, j++)
		dest[i] = src2[j];
	dest[i] = '\0';
	return dest;
}

int check_bsn(char *str)
{
	int ret = -1;

	for (int i = 0; i < READ_SIZE && str[i] != '\0' && ret == -1; i++){
		if (str[i] == '\n')
			ret = i;
	}
	return ret;
}

void save_state(char *buffer, char *state, int bsn, int ret)
{
	int j = 0;

	for (int i = bsn + 1; i <= ret; i++, j++)
		state[j] = buffer[i];
	state[j] = '\0';
}

int restore_state(char **str, char *state)
{
	int bsn = -1;
	int i = 0;
	int j;
	int ret = 0;

	(*str) = my_strcat("", state);
	bsn = check_bsn(state);
	if (bsn != -1){
		for (i, j = bsn + 1; j <= READ_SIZE; i++, j++)
			state[i] = state[j];
		state[i] = '\0';
		ret = 1;
	} else
		for (int k = 0; k <= READ_SIZE; k++)
			state[0] = '\0';
	return ret;
}

char *get_next_line(int fd)
{
	static char state[READ_SIZE + 1];
	char *str = "";
	char buffer[READ_SIZE + 1] = "\0";
	int ret = 1;
	int done = 0;
	int bsn = -1;

	if (restore_state(&str, state) == 1 || fd <= -1)
		return (fd <= -1) ? NULL : str;
	while (done == 0){
		ret = read(fd, buffer, READ_SIZE);
		buffer[ret] = '\0';
		str = my_strcat(str, buffer);
		bsn = check_bsn(buffer);
		if (bsn != -1 || ret <= 0 || str == NULL)
			done = 1;
	}
	if (bsn != -1)
		save_state(buffer, state, bsn, ret);
	return (ret <= 0 && str[0] == '\0') ? NULL : str;
}
