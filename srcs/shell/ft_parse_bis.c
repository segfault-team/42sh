/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:29 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:29 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_waitsons_bbis(t_env *e, t_job *ptr, int status2)
{
	int			i;
	int			status;

	i = 0;
	status = -1;
	while (e->jobs)
	{
		if (!i)
			waitpid(e->jobs->pid, &status, 0);
		else
			waitpid(e->jobs->pid, &status2, 0);
		ptr = e->jobs;
		e->jobs = e->jobs->next;
		if (e->jobs)
			kill(e->jobs->pid, SIGTERM);
		free(ptr);
		++i;
	}
	reset_last_ret(e, WEXITSTATUS(status));
	e->last_cmd_ret = WEXITSTATUS(status);
	e->child_running = 0;
	if (!WEXITSTATUS(status) || !WEXITSTATUS(status2))
		return (1);
	return (-1);
}

int			ft_waitsons(t_env *e)
{
	t_job		*ptr;
	int			now_kill;
	int			status;

	ptr = e->jobs;
	status = 0;
	now_kill = 0;
	ptr = e->jobs;
	while (!now_kill && ptr)
	{
		now_kill = waitpid(ptr->pid, &status, WNOHANG);
		if (!ptr->next)
			ptr = e->jobs;
		else
			ptr = ptr->next;
	}
	return (ft_waitsons_bbis(e, ptr, status));
}

int			ft_check_token(char *s)
{
	char	quote;
	int		tok;
	int		bs;
	int		i;

	quote = '\0';
	tok = 0;
	bs = 0;
	i = -1;
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			if (!bs && s[i] == ';')
				tok++;
			else if (s[i] != ' ')
				tok = 0;
			if (tok > 1)
				return (0);
			bs = 0;
		}
	}
	return (1);
}

/*
** trline is now useless cause tab is not inserted (tcaps directives)
*/

char		**ft_trim_split_cmd(t_env *e)
{
	char	**cmds;

	if (!ft_check_token(e->line))
	{
		ft_printfd(2, "%s: syntax error near unexpected token \";;\"\n",
				SH_NAME);
		return (NULL);
	}
	cmds = ft_split_cmds(e->line, ';');
	return (cmds);
}
