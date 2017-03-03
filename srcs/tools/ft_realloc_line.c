#include "shell.h"

char    *ft_realloc_delete_char(t_env *e, int pos)
{
	char    *new;
	int     len;
	int     i;
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
	i = 0;
	j = -1;
	if (len > 1)
		while (e->line[i])
		{
			if (i != pos)
				new[++j] = e->line[i++];
			else
				++i;
		}
	if (e->line)
		strfree(&e->line);
	return (new);
}

/*
**	ALLOC NEW STR, FREE OLD,
**	COPY OLD IN NEW AND ADD CHAR C
**	AT THE END
*/

char    *ft_realloc_line(t_env *e, char c)
{
	char    *new;
	int     len;
	int     i;

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
	if (e->line)
		strfree(&e->line);
	return (new);
}
