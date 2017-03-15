#include "shell.h"

static int	ft_sslen(char **s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	ft_echo_check(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	if (!*str)
		return (0);
	while (*str && *str == 'n')
		str++;
	if (!*str)
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int cr;
	int i;
	int len;

	cr = 1;
	i = 1;
	len = ft_sslen(args);
	if (len > 1)
	{
		while (args[i] && ft_echo_check(args[i]))
		{
			cr = 0;
			i++;
		}
		while (i < len)
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			i++;
			if (len > i)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (cr)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
