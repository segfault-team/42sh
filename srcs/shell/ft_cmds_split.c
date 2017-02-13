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
		if (!ft_strcmp(e->magic[i].cmd, "|") || !ft_strcmp(e->magic[i].cmd, "<") ||
			!ft_strcmp(e->magic[i].cmd, ">"))
			++len;
	return (len + 1);
}

static int	ft_size_cmd(t_env *e, int *z)
{
	int	len;

	len = 0;
	while (e->magic[++(*z)].cmd && ft_strcmp(e->magic[*z].cmd, "|" ) &&
		   ft_strcmp(e->magic[*z].cmd, ">" ) && ft_strcmp(e->magic[*z].cmd, "<" ))
		++len;
	return (len);
}

static char	**ft_find_tab(t_env *e, int *z)
{
	char	**rtr;
	int		len;
	int		j;
	int		k;

	j = -1;
	k = *z;
	len = ft_size_cmd(e, z);
	if (!(rtr = (char **)malloc(sizeof(*rtr) * (len + 1))))
//MANAGE ERROR
		return (NULL);
	rtr[len] = NULL;
	while (++j < len)
		rtr[j] = ft_strdup(e->magic[++k].cmd);
	return (rtr);
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
