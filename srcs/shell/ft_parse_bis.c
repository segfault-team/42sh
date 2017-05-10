/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:19 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/10 14:52:18 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_last_cmd_ret(t_env *e, int status, int status2, int i)
{
	if (i)
	{
		if (ft_handle_ret_signal(status) == -1)
			e->last_cmd_ret = WTERMSIG(status);
		else
			e->last_cmd_ret = WEXITSTATUS(status);
	}
	e->child_running = 0;
	if (!e->last_pipe_ret && ((child_is_signaled(status)
					|| child_is_signaled(status2)) || (!WEXITSTATUS(status)
					|| !WEXITSTATUS(status2))))
		return (1);
	return (-1);
}

int			ft_waitsons_bbis(t_env *e, int lol, int status, t_job *ptr)
{
	int			i;
	int			status2;

	i = 0;
	status2 = -1;
	while (e->jobs)
	{
		if (e->jobs->pid != -1)
		{
			if (!i)
				waitpid(e->jobs->pid, &status, WUNTRACED);
			else
				waitpid(e->jobs->pid, &status2, WUNTRACED);
		}
		ptr = e->jobs;
		e->jobs = e->jobs->next;
		if (e->jobs && e->jobs->pid != -1)
			kill(e->jobs->pid, SIGTERM);
		free(ptr);
		++i;
	}
	return (ft_last_cmd_ret(e, status, status2, i));
}

int			ft_waitsons(t_env *e)
{
	int		status;
	int		lol;
	int		now_kill;
	t_job	*ptr;

	lol = 0;
	status = -1;
	now_kill = 0;
	if (!e->jobs)
		return (-1);
	ptr = e->jobs;
	while (!lol && !now_kill && ptr)
	{
		if (ptr->pid != -1)
			now_kill = waitpid(e->jobs->pid, &status, WNOHANG);
		else
			lol = 1;
		if (ptr->next)
			ptr = ptr->next;
		else
			ptr = e->jobs;
	}
	return (ft_waitsons_bbis(e, lol, status, ptr));
}

static int	ft_check_token(char *s, char quote)
{
	int		tok;
	int		bs;
	int		i;

	tok = 0;
	bs = 0;
	i = -1;
	while (s && ++i < (int)ft_strlen(s) && s[i])
	{
		quote = s[i] ? ft_check_quote_bs(s[i], quote, bs) : '\0';
		if (!bs && s[i] && s[i] == '\\' && quote != '\'')
			bs = 1;
		else if (!quote)
		{
			if (!bs && s[i] && s[i] == ';')
				tok++;
			else if (s[i] && s[i] != ' ')
				tok = 0;
			if (tok > 1)
				return (0);
			bs = 0;
		}
	}
	return (1);
}

char		**ft_trim_split_cmd(t_env *e)
{
	char	**cmds;

	if (!ft_check_token(e->line, '\0'))
	{
		ft_printfd(2, "%s: syntax error near unexpected token \";;\"\n",
				SH_NAME);
		return (NULL);
	}
	cmds = ft_split_cmds(e->line, ';');
	return (cmds);
}
