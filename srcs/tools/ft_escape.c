#include "shell.h"

int			ft_is_escaped(char *str, int i)
{
	int ret;

	ret = 0;
	if (!i)
		return (0);
	i--;
	while (str[i] && i >= 0 && str[i] == '\\')
	{
		if (str[i] == '\\')
			ret = ret ? 0 : 1;
		i--;
	}
	return (ret);
}

int			ft_is_escape_after(char *str, int i)
{
	int ret;

	ret = 0;
	if (!str[i])
		return (0);
	i++;
	while (str[i] && i >= 0 && str[i] == '\\')
	{
		if (str[i] == '\\')
			ret = ret ? 0 : 1;
		i++;
	}
	return (ret);
}
