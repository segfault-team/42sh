/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:22:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/17 21:43:57 by lfabbro          ###   ########.fr       */
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
	tmp = NULL;
	if ((tmp = ft_getenv(e->env, "HOME")))
	{
		e->home = ft_strdup(tmp);
		return (1);
	}
	return (0);
}

static void		ft_set_shlvl(t_env *e)
{
	char	*lvl;
	int		tmp;

	if ((lvl = ft_getenv(e->env, "SHLVL")))
	{
		tmp = ft_atoi(lvl) + 1;
		lvl = ft_itoa(tmp);
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
	e->history = NULL;
	e->env = ft_tabdup(env);
	ft_check_file_perm(HIST_FILE);
	if (e->env == NULL || !ft_set_home(e))
		ft_error(SH_NAME, "warning: no home set", NULL);
	if (ft_read_history(e) < 0)
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	e->x = 1;
	e->exit = 0;
	e->line = NULL;
	e->cmd = NULL;
	e->cut = NULL;
	e->cat = NULL;
	ft_bzero(e->buf, 3);
	ft_set_prompt(e);
	ft_set_shlvl(e);
	tcaps_init(e);
}
