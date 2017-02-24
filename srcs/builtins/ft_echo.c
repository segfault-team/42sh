/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:38:01 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/23 15:11:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
int			ft_echo(t_env *e)
>>>>>>> origin/redirections_clean
{
	int		i;
	int		nl;
	size_t	cmd_len;

	i = 0;
	if (e)
		;
	cmd_len = ft_tablen(cmd);
	if ((nl = ft_strequ(cmd[1], "-n")))
		++i;
	while (cmd[++i])
	{
<<<<<<< HEAD
		if ((!nl && i == 2) || (i > 2 && i < (int)cmd_len))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd[i], 1);
=======
		if ((!nl && i == 2) || (i > 2 && i < (int)e->cmd_len))
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(e->cmd[i], STDOUT_FILENO);
>>>>>>> origin/redirections_clean
	}
	if (!nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
*/

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
	return (1);
}
