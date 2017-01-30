#include "shell.h"

/*
**	CHECK IF THE CURRENT KEY IS
**		THE ONE WE WANT
*/

int check_key(char buf[3], int a, int b, int c)
{
	if (buf[0] == (char)a && buf[1] == (char)b && buf[2] == (char)c)
		return (1);
	return (0);
}

/*
**	CHECK IF THE CURRENT KEY IS
**		PRINTABLE CHAR
*/

int check_read(char buf[3])
{
	if (!buf[1] && !buf[2] && (buf[0] >= 32 && buf[0] < 126))
		return (1);
	return (0);
}
