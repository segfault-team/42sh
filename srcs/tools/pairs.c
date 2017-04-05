#include "shell.h"

int		check_pairs(char *str, char c, char d)
{
	int		open;
	int		close;
	int		i;

	open = 0;
	close = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			++open;
		else if (str[i] == d)
			++close;
	}
	if (((open + close) % 2) != 0)
		return ((open > close) ? c : d);
	return (0);
}

int		ft_pairs(char *str)
{
	char	ret;
	char	c;

	ret = check_pairs(str, '(', ')');
	ret = !ret ? check_pairs(str, '{', '}') : ret;
	ret = !ret ? check_pairs(str, '[', ']') : ret;
	if (ret)
		ft_printfd(2, "\nSyntax error near unexpected token: \'%c\'\n", ret);
	return (!ret ? 1 : 0);
}
