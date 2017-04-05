#include "shell.h"

int		ft_waitsons(t_env *e)
{
	t_job		*tmp;
	int			status;

	tmp = NULL;
	status = 0;
	while (e->jobs)
	{
		waitpid(e->jobs->pid, &status, WUNTRACED);
		ft_handle_ret_signal(status);
		tmp = e->jobs->next;
		free(e->jobs);
		e->jobs = tmp;
	}
	e->child_running = 0;
	if (!status)
		return (1);
	return (-1);
}

int		ft_check_token(char *s)
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

char	**ft_trim_split_cmd(t_env *e)
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
