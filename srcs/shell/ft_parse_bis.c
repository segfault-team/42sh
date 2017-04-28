/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:19 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 17:48:30 by lfabbro          ###   ########.fr       */
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
	if (!e->last_pipe_ret && (!WEXITSTATUS(status) || !WEXITSTATUS(status2)))
		return (1);
	return (-1);
}

int			ft_waitsons(t_env *e)
{
	int			i;
	int			status;
	int			status2;
	t_job		*ptr;

	i = 0;
	status = -1;
	status2 = -1;
	while (e->jobs)
	{
		if (!i)
			waitpid(e->jobs->pid, &status, WUNTRACED);
		else
			waitpid(e->jobs->pid, &status2, WUNTRACED);
		ptr = e->jobs;
		e->jobs = e->jobs->next;
		if (e->jobs)
			kill(e->jobs->pid, SIGTERM);
		free(ptr);
		++i;
	}
	return (ft_last_cmd_ret(e, status, status2, i));
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
		quote = ft_check_quote_bs(s[i], quote, bs);
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else if (!quote)
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

	if (!ft_check_token(e->line, '\0'))
	{
		ft_printfd(2, "%s: syntax error near unexpected token \";;\"\n",
				SH_NAME);
		return (NULL);
	}
	cmds = ft_split_cmds(e->line, ';');
	return (cmds);
}
