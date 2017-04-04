#include "shell.h"

/*
**	COUNT THE NUMBER OF REDIRECTIONS IN CMD
**	TODO: ajouter reconnaissance de "&&" "||" "n%>n"
*/

static int	ft_nb_cmds(t_env *e)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (e->magic[++i].cmd)
	{
		if ((is_redirection(e, i) || is_operator(e, i))
			&& !is_aggregator(e, i)
			&& !is_input_redir(e, i) && !is_heredoc(e, i))
		{
			if (!is_output_redir(e, i) && !is_input_redir(e, i))
				++len;
		}
	}
	return (len + 1);
}

static int	ft_nb_elem_cmd(t_env *e, int *z)
{
	int			len;
	static int	last_cmd = 0;

	len = 0;
	while (++(*z) < e->len_mag && e->magic[(*z)].cmd
		   && !is_redir_pipe(e, *z) && !is_operator(e, *z))
	{
		if (e->magic[*z].type && !ft_strcmp(e->magic[*z].type, "cmd"))
			++len;
	}
	return (len);
}

static char	**ft_find_tab(t_env *e, int *z)
{
	char	**ret;
	int		len;
	int		j;
	int		k;

	j = 0;
	k = *z;
	len = ft_nb_elem_cmd(e, z);
	if (!(ret = ft_tabnew(len + 1)))
		return (NULL);
	ft_tabzero(ret, len);
	while (j < len && e->magic[++k].cmd)
	{
		if (!is_redirection(e, k) && !is_input_file(e, k)
			&& ft_strcmp(e->magic[k].type, "output")
			&& ft_strcmp(e->magic[k].type, "heredoc")
			&& ft_strcmp(e->magic[k].type, "fd_aggregator")
			&& ft_strcmp(e->magic[k].type, "operator"))
			if ((ret[j++] = ft_strdup_wo_quote_bs(e->magic[k].cmd)) == NULL)
				return (ret);
	}
	return (ret);
}

/*
**	CREATE AND RETURN A 3D TAB
**	WHICH CONTAIN ALL CMDS
*/

char		***ft_cmds_split(t_env *e)
{
	char	***cat;
	int		len;
	int		i;
	int		z;

	len = ft_nb_cmds(e);
	i = -1;
	z = -1;
	if (!(cat = (char ***)malloc(sizeof(*cat) * (len + 1))))
		return (NULL);
	cat[len] = NULL;
	while (++i < len)
	{
		if (!(cat[i] = ft_find_tab(e, &z)))
			return (cat);
	}
	return (cat);
}
