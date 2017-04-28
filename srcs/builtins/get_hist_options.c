/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hist_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:09:46 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:09:46 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	manage_suspend_opt(int i, char **cmd, t_opt_hist *opt)
{
	if (cmd[i + 1] && !is_only_numbers(cmd[i + 1]))
	{
		return (ft_error("history", cmd[1 + 1],
						"numeric argument required"));
	}
	return (manage_opt_hist_priority(opt));
}

static int	hist_invalid_option(char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_error("history", "invalid option", tmp));
}

static int	get_opt_in_one_arg(int i, char **cmd, t_opt_hist *opt)
{
	int	j;
	int	len;
	int	opt_d;

	len = (int)ft_tablen(cmd);
	j = -1;
	while (i < len && cmd[i][++j])
	{
		opt_d = 0;
		if (!j && !is_only_numbers(cmd[i]) && cmd[i][j] != '-')
			return (ft_error("history", cmd[i], "numeric argument required"));
		else if (is_valid_opt(cmd[i][j]))
			add_opt(opt, cmd[i][j], &opt_d, i);
		else if (cmd[i][j] == '-' && cmd[i][j + 1] && cmd[i][j + 1] == '-')
			return (manage_suspend_opt(i, cmd, opt));
		else if (cmd[i][j] != '-' && !is_number(cmd[i][j]))
			return (hist_invalid_option(cmd[i][j]));
		else if (j && !is_only_numbers(cmd[i]))
			return (ft_error("history", cmd[i], "numeric argument required"));
		if (opt_d && cmd[i + 2])
			++i;
		if (opt->p)
			return (42);
	}
	return (1);
}

int			get_hist_options(int i, char **cmd, t_opt_hist *opt)
{
	int	j;
	int	len;
	int	ret;

	len = (int)ft_tablen(cmd);
	ret = 0;
	while (ret != 42 && i < len && cmd[i])
	{
		j = -1;
		if ((ret = get_opt_in_one_arg(i, cmd, opt)) == -1)
			return (-1);
		++i;
	}
	return (manage_opt_hist_priority(opt));
}
