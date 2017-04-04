#include "shell.h"

/*
**	DELETE ALL ELEMENT IN TAB
**	AFTER INDEX
*/

void		ft_cut_tab(char **pas_tab, int i)
{
	while (pas_tab[i])
	{
		free(pas_tab[i]);
		pas_tab[i] = NULL;
		i++;
	}
}

static int	nb_valid_types(t_env *e)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (e->magic[++i].type != NULL)
	{
		if (ft_strcmp("ignore", e->magic[i].type))
			len++;
	}
	return (len);
}

void		magic_realloc(t_env *e)
{
	int		i;
	int		j;
	t_magic	*new;

	i = -1;
	j = -1;
	if (!(new = (t_magic *)malloc(sizeof(t_magic) * (nb_valid_types(e) + 1))))
		return ;
	while (e->magic[++i].type)
	{
		if (ft_strcmp(e->magic[i].type, "ignore"))
		{
			new[++j].type = ft_strdup(e->magic[i].type);
			new[j].cmd = ft_strdup(e->magic[i].cmd);
		}
	}
	new[++j].cmd = NULL;
	new[j].type = NULL;
	magic_free(e);
	e->magic = new;
}
