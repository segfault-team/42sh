/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:22:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/21 08:15:26 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_set_prompt(t_env *e)
{
	e->prompt = ft_strdup("$> ");
}

static int		ft_set_home(t_env *e)
{
	char		*tmp;

	e->home = NULL;
	if ((tmp = ft_find_name(e->env, "HOME")))
	{
		e->home = ft_strdup(ft_strchr(tmp, '=') + 1);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static void		ft_set_shlvl(t_env *e)
{
	char	*lvl;
	int		tmp;

	if ((lvl = ft_find_value(e->env, "SHLVL")))
	{
		tmp = ft_atoi(lvl) + 1;
		free(lvl);
		lvl = ft_itoa(tmp);
		ft_unsetenv(&e->env, "SHLVL");
		ft_setenv(&e->env, "SHLVL", lvl);
		free(lvl);
	}
	else
		ft_setenv(&e->env, "SHLVL", "1");
}

void			ft_init(t_env *e, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	FDOUT = 1;
	FDIN = 1;
	e->x = 1;
	e->exit = 0;
	e->line = NULL;
	e->env = ft_tabdup(env);
	ft_set_prompt(e);
	ft_set_shlvl(e);
	if (e->env == NULL || !ft_set_home(e))
		ft_error("minishell", "warning: no home set", NULL);
}
