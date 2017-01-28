#include "shell.h"

/*
**	ALLOC NEW STR, FREE OLD,
**	COPY OLD IN NEW AND INSERT
**	CHAR C AT THE INDEX DEFINE
*/

char    *realloc_insert_char(t_env *e, char c)
{
	char    *new;
	int     len;
	int     i;
	int		j;
	int		isrt;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	new = (char*)malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	i = 0;
	j = -1;
	isrt = TCAPS.nb_read - TCAPS.nb_move;
	if (len != 1)
		while (e->line[i])
		{
			if (i != isrt || !c)
				new[++j] = e->line[i++];
			else
			{
				new[++j] = c;
				c = '\0';
			}
		}
	if (e->line)
	{
		free(e->line);
		e->line = NULL;
	}
	return (new);
}

/*
**	ALLOC NEW STR, FREE OLD,
**	COPY OLD IN NEW AND ADD CHAR C
**	AT THE END
*/

char    *realloc_line(t_env *e, char c)
{
	char    *new;
	int     len;
	int     i;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	new = (char*)malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	i = 0;
	if (len != 1)
		while (e->line[i])
		{
			new[i] = e->line[i];
			++i;
		}
	new[i] = c;
	if (e->line)
	{
		free(e->line);
		e->line = NULL;
	}
	return (new);
}
