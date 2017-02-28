#include "shell.h"

/*
**	Takes a range of char (args are int for easier management) and return \
**	a string containing every char in this interval.
*/

char	*glob_range(int start, int end)
{
	int		len;
	char	*ret;
	int		i;

	i = -1;
	if (end > start)
		len = end - start;
	else
		return (NULL);
	ret = ft_strnew(len);
	while (++i < len)
	{
		ret[i] = (char)start;
		++start;
	}
	return (ret);
}
