#include "shell.h"

/*
**	Replace the '?' in str by every char between 32 and 126 and check \
**	if the result match with cmp
*/

static int		find_symbol(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '?')
			return (i);
	return (-1);
}

int				glob_single(char *str, char *cmp)
{
	int		sym;
	int		i;

	if ((sym = find_symbol(str)) < 0)
		return (0);
	i = sym;
	str[i] = 32;
	while (str[i] < 127 && ft_strcmp(str, cmp))
		++str[i];
	if (ft_strcmp(str, cmp))
		return (1);
	return(0);
}
