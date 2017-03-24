#include "shell.h"

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_only_numbers(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_number(str[i]))
			return (0);
	return (1);
}
