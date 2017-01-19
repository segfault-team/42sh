/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 17:24:45 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 23:14:11 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	ft_arglen(t_env *e, int i)
{
	size_t	len;

	len = (size_t)i;
	while (++len < e->cmd_len && ft_strchr(e->cmd[len], '='))
		;
	return (len);
}

static int		ft_arg_isdouble(char **args, char *arg, int i)
{
	char	*eval;
	char	**tmp;

	tmp = ft_strsplit(arg, '=');
	eval = ft_strjoin(tmp[0], "=");
	ft_free_tab(tmp);
	while (args[++i])
		if (ft_strnequ(args[i], eval, ft_strlen(eval)))
		{
			free(eval);
			return (1);
		}
	free(eval);
	return (0);
}

static int		ft_opt_i(t_env *e, char ***env_cpy, int i)
{
	char	**ptr;
	size_t	len;
	int		j;

	len = ft_arglen(e, i);
	ft_free_tab(*env_cpy);
	*env_cpy = ft_tabnew(len + 1);
	ptr = *env_cpy;
	j = 0;
	while (++i < (int)len)
	{
		if (e->cmd[i][0] == '=')
			return (ft_error("env", "invalid argument", e->cmd[i]));
		if (!ft_arg_isdouble(e->cmd, e->cmd[i], i))
		{
			ptr[j] = ft_strdup(e->cmd[i]);
			++j;
		}
	}
	if (len == e->cmd_len)
	{
		ft_puttab(*env_cpy);
		return (-1);
	}
	return (i);
}

static int		ft_env_opt(t_env *e, char ***env_cpy)
{
	int		i;

	i = 0;
	while (++i < (int)e->cmd_len && e->cmd[i] && e->cmd[i][0] == '-')
	{
		if (e->cmd[i][1] == 'u' && e->cmd[i + 1])
		{
			ft_unsetenv(env_cpy, e->cmd[i + 1]);
			++i;
		}
		else if (e->cmd[i][1] == 'i')
			return (ft_opt_i(e, env_cpy, i));
		else
		{
			ft_error("env", "illegal option --", &e->cmd[i][1]);
			ft_error("usage", "env [-i name1=val1 ...] [-u name]", NULL);
			return (0);
		}
	}
	if (i == (int)e->cmd_len)
	{
		ft_puttab(*env_cpy);
		return (-1);
	}
	return (i);
}

int				ft_env(t_env *e)
{
	char	**env_cpy;
	int		i;

	env_cpy = ft_tabdup(e->env);
	if (e->cmd_len > 1)
	{
		if ((i = ft_env_opt(e, &env_cpy)) > 0)
		{
			ft_exec(&e->cmd[i], env_cpy);
		}
	}
	else
		ft_puttab(e->env);
	ft_free_tab(env_cpy);
	return (0);
}
