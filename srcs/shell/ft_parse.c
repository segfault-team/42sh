#include "shell.h"

int		ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv") ||
			!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") ||
			!ft_strcmp(cmd, "where") || !ft_strcmp(cmd, "history") ||
			!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int		ft_exec_builtin(t_env *e, char **cmd)
{
	char	ret;

	ret = 0;
	redirection_before_cmd(e);
	ft_redirect(FD.in, STDIN_FILENO);
	close(FD.fd[1]);
	if (!ft_strcmp(cmd[0], "exit") && ++ret)
		ft_exit(e);
	else if (!ft_strcmp(cmd[0], "env") && ++ret)
		ret = ft_env(e, cmd);
	else if (!ft_strcmp(cmd[0], "setenv") && ++ret)
		ret = ft_setenv_blt(e, cmd);
	else if (!ft_strcmp(cmd[0], "unsetenv") && ++ret)
		ret = ft_unsetenv_blt(e, cmd);
	else if (!ft_strcmp(cmd[0], "cd") && ++ret)
		ret = ft_cd(e, cmd);
	else if (!ft_strcmp(cmd[0], "pwd") && ++ret)
		ret = ft_pwd(e, cmd);
	else if (!ft_strcmp(cmd[0], "echo") && ++ret)
		ret = ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "where") && ++ret)
		ret = ft_where(e, cmd);
	else if (!ft_strcmp(cmd[0], "history") && ++ret)
		ret = ft_history(e, cmd, 1);
	return (ret);
}

int				ft_waitsons(t_env *e)
{
	t_job		*ptr;
	t_job		*tmp;
	int			status;

	ptr = e->jobs;
	while (ptr)
	{
		waitpid(ptr->pid, &status, WUNTRACED);
		ft_handle_ret_signal(status);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	e->child_running = 0;
	e->jobs = NULL;
	return (0);
}

/*
** trline is now useless cause tab is not inserted (tcaps directives)
*/

char		**ft_trim_split_cmd(t_env *e)
{
	char	**cmds;
	char	*trline;

	if (!(trline = ft_strxtrim_quote(e->line, '\t')))
	{
		ft_printfd(2, "%s: syntax error near unexpected token \";;\"\n",
				   SH_NAME);
		return (NULL);
	}
	cmds = ft_split_cmds(trline, ';');
	ft_strdel(&trline);
	return (cmds);
}

int				ft_iter_cmds(t_env *e, char *cmds_i)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	FD.in = STDIN_FILENO;
	if (!(e->cmd = ft_strsplit_quote_bs(cmds_i, ' ')) ||
		!(e->magic = struct_strsplit_wo_quote_bs(cmds_i, ' ')))
		return (ft_error(SH_NAME, "parsing error.", NULL));
	if (magic_type(e) == -1)
		return (-42);
	if ((e->cat = ft_cmds_split(e)) == NULL)
		return (-1);
	ft_create_file(e);
/*	ft_printf("====  MAGIC  ====\n");
	for (int j = 0 ; e->magic[j].cmd ; j++)
		ft_printfd(2, "cmd[%d]: %s | type: %s\n", j, e->magic[j].cmd, e->magic[j].type);
	ft_printf("====   CAT       ====\n");
	for (int k = 0 ; e->cat[k] ; ++k)
		for (int l = 0 ; e->cat[k][l] ; ++l)
			ft_printf("cat[%d][%d]: %s\n", k, l, e->cat[k][l]);
	ft_printf("====  END CAT    ====\n");
*/	while (e->cat[++i] && ret != -1)
	{
		while (is_aggregator(e, RED_INDEX)
			   || is_output_redir(e, RED_INDEX) || is_heredoc(e, RED_INDEX))
			struct_find_red(e);
		if (!e->cat[i + 1] && redir_check_red(e, "|")
			&& is_next_redir(e, RED_INDEX) == OUTPUT)
			ret = redir_exec_open(i, e);
		else if ((!e->cat[i + 1] && redir_check_red(e, "|")) ||
			(!RED_INDEX && redir_check_red(e, "|")))
		{
			FD.fd[1] = STDOUT_FILENO;
			if (is_next_redir(e, RED_INDEX) == AGGREGATOR)
				struct_find_red(e);
			ret = ft_exec_cmd(e, e->cat[i]);
		}
		else
			ret = redir_exec_open(i, e);
		reset_last_ret(e, ret);
		if (is_output_redir(e, RED_INDEX))
			redir_fill_output(e);
		dup2(FD.stdin, STDIN_FILENO);
		dup2(FD.stdout, STDOUT_FILENO);
		dup2(FD.stderr, STDERR_FILENO);
	}
	ft_waitsons(e);
	ft_triple_free(e);
	ft_free_tab(e->hdoc_words);
	e->hdoc_words = NULL;
	magic_free(e);
	RED_INDEX = 0;
	ft_tabfree(e->cmd);
	e->cmd = NULL;
	return (ret);
}

int				ft_parse_line(t_env *e)
{
	int		i;
	int		ret;
	char	**cmds;

	i = -1;
	ret = 0;
	if (substitution(e) == -1)
		return (-1);
	ft_store_history(e);
	if ((cmds = ft_trim_split_cmd(e)) != NULL)
	{
		while (cmds[++i])
		{
			ret = ft_iter_cmds(e, cmds[i]);
			if (ret == -42)
				return (ret);
			tcaps_set(e);
		}
	}
	ft_free_tab(cmds);
	return (ret);
}
