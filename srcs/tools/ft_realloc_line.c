#include "shell.h"

char	*ft_realloc_delete_char(t_env *e, int pos)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	if (e->line)
		len = NB_READ - 1;
	else
		return (NULL);
	if (!(new = ft_strnew(len)))
	{
		strfree(&e->line);
		return (NULL);
	}
	i = -1;
	j = -1;
	if (len > 1)
		while (e->line[++i])
			if (i != pos)
				new[++j] = e->line[i];
	strfree(&e->line);
	return (new);
}

/*
**	Appends new character at the end of line
**	(realloc it)
*/

char	*ft_realloc_line(t_env *e, char c)
{
	char	*new;
	int		len;
	int		i;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = 0;
	if (len != 1)
		while (e->line[i])
		{
			new[i] = e->line[i];
			++i;
		}
	new[i] = c;
	strfree(&e->line);
	return (new);
}
