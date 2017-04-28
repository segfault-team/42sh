/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:08:57 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:08:57 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_env_opt_u(char ***env_cpy, char **cmd, int i)
{
	if (!cmd[i])
		return (ft_env_opt_u_error(NULL));
	else if (ft_strchr(cmd[i], '='))
		return (ft_env_opt_u_error(cmd[i]));
	if (ft_unsetenv(env_cpy, cmd[i]) == -1)
		return (1);
	return (0);
}

static int		ft_env_opt_i(char ***env_cpy)
{
	ft_free_tab(*env_cpy);
	*env_cpy = NULL;
	env_cpy = NULL;
	return (0);
}

static int		ft_env_opt(char ***env_cpy, size_t len, char **cmd, int i)
{
	int			j;
	int			ret;

	while (++i < (int)len && cmd[i] &&
			cmd[i][0] == '-' && !ft_strchr(cmd[i], '=') && !(j = 0))
	{
		while (cmd[i][0] == '-' && cmd[i][++j])
		{
			if (cmd[i][j] == 'i')
			{
				if (!ft_env_opt_i(env_cpy) && i > 1)
					break ;
			}
			else if (cmd[i][j] == 'u' && !cmd[i][j + 1])
			{
				if ((ret = ft_env_opt_u(env_cpy, cmd, ++i)) == -1)
					return (-1);
				else if (ret == 1)
					break ;
			}
			else if (cmd[i][1] != 'u' && cmd[i][1] != 'i')
				return (ft_env_error(cmd[i]));
		}
	}
	return (i);
}

static int		ft_env_bis(t_env *e, char ***env_cpy, char **cmd, int i)
{
	while (cmd[i] && ft_strchr(cmd[i], '='))
	{
		if (cmd[i][0] == '=')
			return (ft_error2("env", "setenv", cmd[i], "invalid argument"));
		if (ft_insert_arg(env_cpy, cmd[i++]))
			break ;
	}
	e->env = *env_cpy;
	if (cmd[i])
	{
		e->env_exec = 1;
		i = ft_exec_cmd(e, &cmd[i]);
	}
	else
		ft_puttab(e->env);
	return (0);
}

int				ft_env(t_env *e, char **cmd)
{
	char	**env_cpy;
	char	**tmp;
	size_t	len;
	int		i;

	i = 1;
	env_cpy = ft_tabdup(e->env);
	tmp = e->env;
	if ((len = ft_tablen(cmd)) > 1)
	{
		if ((i = ft_env_opt(&env_cpy, len, cmd, 0)) > 0)
		{
			if (ft_env_bis(e, &env_cpy, cmd, i) == -1)
				i = 0;
		}
	}
	else
		ft_puttab(e->env);
	ft_free_tab(env_cpy);
	e->env = tmp;
	if (!i)
		return (1);
	return (i);
}
