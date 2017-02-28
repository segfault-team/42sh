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
		if (!ft_strcmp(e->magic[i].cmd, "|") || !ft_strcmp(e->magic[i].cmd, "<") ||
			!ft_strcmp(e->magic[i].cmd, ">") || !ft_strcmp(e->magic[i].cmd, ">>"))
		{
			++len;
			if (!ft_strcmp(e->magic[i].cmd, ">") || !ft_strcmp(e->magic[i].cmd, ">>"))
				return (len + 1);
		}
	}
	return (len + 1);
}

static int	ft_nb_elem_cmd(t_env *e, int *z)
{
	int			len;
	static int	last_cmd = 0;

	len = 0;
	if (last_cmd)
	{
		while (e->magic[++(*z)].cmd && ft_strcmp(e->magic[*z].cmd, "|" ))
		{
			if (ft_strcmp(e->magic[*z].cmd, ">") || ft_strcmp(e->magic[*z].cmd, ">>"))
				++len;
		}
		last_cmd = 0;
	}
	else
	{
		while (e->magic[++(*z)].cmd && ft_strcmp(e->magic[*z].cmd, "|") && ft_strcmp(e->magic[*z].cmd, ">")\
			&& ft_strcmp(e->magic[*z].cmd, ">>"))
			++len;
		if (!ft_strcmp(e->magic[*z].cmd, ">") || !ft_strcmp(e->magic[*z].cmd, ">>"))
			++last_cmd;
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
	if (!(ret = (char **)malloc(sizeof(*ret) * (len + 1))))
// MANAGE ERROR
		return (NULL);
	ft_tabzero(ret, len);
	while (j < len && e->magic[++k].cmd)
	{
		if (ft_strcmp(e->magic[k].cmd, ">") && ft_strcmp(e->magic[k].cmd, ">>"))
			ret[j++] = ft_strdup(e->magic[k].cmd);
	}
	return (ret);
}

/*
**	CREATE AND RETURN A 3D TAB
**	WHO CONTAIN ALL CMDS
*/

char	***ft_cmds_split(t_env *e)
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
		cat[i] = ft_find_tab(e, &z);
	return (cat);
}
