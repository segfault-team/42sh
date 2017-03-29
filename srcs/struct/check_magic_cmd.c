#include "shell.h"

char	*clean_from_space(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = -1;
	k = -1;
	while (str[++i] && str[i] == ' ')
		;
	j = (int)ft_strlen(str);
	while (str[--j] == ' ')
		;
	if (j - i == (int)ft_strlen(str) - 1)
		return (str);
	new = ft_strnew(j - i);
	while (i <= j)
		str[++k] = str[i++];
	return (str);
}

void	check_magic_cmd(t_env *e)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (e->magic[++i].cmd)
	{
		tmp = e->magic[i].cmd;
		e->magic[i].cmd = clean_from_space(e->magic[i].cmd);
		if (ft_strcmp(e->magic[i].cmd, tmp))
			strfree(&tmp);
	}
}
