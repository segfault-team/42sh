#include "shell.h"

int	isNumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	isOnlyNumbers(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!isNumber(str[i]))
			return (0);
	return (1);
}
