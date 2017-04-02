#include "shell.h"

static int		exec_by_type(t_env *e, int i, int ret)
{
	if (!e->cat[i + 1] && redir_check_red(e, "|")
		&& is_next_redir(e, RED_INDEX) == OUTPUT)
	{
		ret = redir_exec_open(i, e);
	}
	else if (!e->cat[i + 1] && redir_check_red(e, "|"))
	{
		FD.fd[1] = STDOUT_FILENO;
		if (is_next_redir(e, RED_INDEX) == AGGREGATOR)
			struct_find_red(e);
		ret = ft_exec_cmd(e, e->cat[i]);
	}
	else
		ret = redir_exec_open(i, e);
	if (find_next_output(e, find_last_pipe(e)))
		redir_fill_output(e);
	dup2(FD.stdin, STDIN_FILENO);
	dup2(FD.stdout, STDOUT_FILENO);
	dup2(FD.stderr, STDERR_FILENO);
	return (ret);
}

static void		exec_end(t_env *e)
{
	ft_waitsons(e);
	ft_triple_free(e);
	ft_free_tab(e->hdoc_words);
	e->hdoc_words = NULL;
	magic_free(e);
	RED_INDEX = 0;
	ft_tabfree(e->cmd);
	e->cmd = NULL;
	e->check_input = 0;
}

/*int				do_all_substitution(t_env *e, int i)
{
	int x;
	int ret;

	ret = 0;
	x = 0;
	while (e->cat && e->cat[i] && e->cat[i][x])
	{
		if (substitution(e, i, x) == -1)
			ret = -1;
		if (!e->cat[i][x][0])
			ret = -1;
		x++;
	}
	return (ret);
}*/

int				ft_iter_cmds(t_env *e, char *cmds_i)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	FD.in = STDIN_FILENO;
	if (!(e->cmd = ft_strsplit_wo_quote_bs(cmds_i, ' ')) ||
		!(e->magic = struct_strsplit_wo_quote_bs(cmds_i, ' ')))
		return (ft_error(SH_NAME, "parsing error.", NULL));
	if (magic_type(e) == -1)
		return (-42);
	e->len_mag = struct_len(&e->magic);
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
*/
	while (++i < ft_catlen(e->cat) && e->cat[i])
	{
		ret = exec_by_type(e, i, ret);
		i += manage_operators(e, RED_INDEX, ret);
	}
	exec_end(e);
	return (ret);
}

static void	manage_quote(char *quote, char current)
{
	if (!(*quote))
		*quote = current;
	else if (current == *quote)
		*quote = '\0';
}

int 			test(t_env *e)
{
	int		i;
	int		ret;
	char	quote;

	i = -1;
	ret = 0;
	quote = '\0';
	while (e->line[++i])
	{
		if (ret == -1)
			return (-1);
		if ((e->line[i] == '"' || e->line[i] == '\'') && i - 1 >= 0 &&
			e->line[i - 1] != '\\')
			manage_quote(&quote, e->line[i]);
		else if (e->line[i] == '!' && !quote)
			ret = manage_exclamation_mark(e, &i);
	}
	if (ret)
		ft_printf("%s\n", e->line);
	return (ret);
}

int				ft_parse_line(t_env *e)
{
	int		i;
	int		ret;
	char	**cmds;

	i = -1;
	ret = 0;
	if (test(e) == -1)
		return (-1);
	ft_store_history(e);
	if ((cmds = ft_trim_split_cmd(e)) != NULL)
	{
		if (!cmds[0])
			ft_printfd(2, "%s: syntax error near unexpected token \";\"\n",
					   SH_NAME);
		while (cmds[++i])
		{
			if (substitution(e, &cmds[i]) == -1)
				ret = -42;
			else
				ret = ft_iter_cmds(e, cmds[i]);
			if (ret == -42)
				return (ret);
			tcaps_set(e);
		}
	}
	ft_free_tab(cmds);
	return (ret);
}
