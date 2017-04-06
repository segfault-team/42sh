#include "shell.h"

static int	ft_waitsons_bbis(t_env *e, t_job *ptr, int status)
{
	int			i;
	int			status2;

	i = 0;
	while (e->jobs)
	{
		kill(e->jobs->pid, SIGTERM);
		if (!i)
			waitpid(e->jobs->pid, &status, WNOHANG);
		else
			waitpid(e->jobs->pid, &status2, WNOHANG);
		ptr = e->jobs;
		e->jobs = e->jobs->next;
		free(ptr);
		++i;
	}
	reset_last_ret(e, WEXITSTATUS(status));
	e->last_cmd_ret = WEXITSTATUS(status);
	e->child_running = 0;
	if (!status)
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

char			**ft_trim_split_cmd(t_env *e)
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
