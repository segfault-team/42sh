#include "shell.h"

/*
**	ALLOC NEW STR, FREE OLD,
**	COPY OLD IN NEW AND INSERT
**	CHAR C AT THE INDEX DEFINE
*/

static char	*realloc_char(t_env *e, char *new, char c)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (e->line[i])
	{
		if (i != NB_MOVE || !c)
			new[++j] = e->line[i++];
		else
		{
			new[++j] = c;
			c = '\0';
		}
	}
	return (new);
}

char	*ft_realloc_insert_char(t_env *e, char c)
{
	char	*new;
	int		len;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	if ((new = ft_strnew(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (len != 1)
		new = realloc_char(e, new, c);
	strfree(&e->line);
	return (new);
}

void	ft_realloc_insert_str(t_env *e, char *str)
{
	char	*new;
	char	*tmp;

	new = ft_strsub(e->line, 0, TCAPS.nb_move);
	tmp = ft_strjoin(new, str);
	free(new);
	if (TCAPS.nb_read > TCAPS.nb_move)
		new = ft_strsub(e->line, TCAPS.nb_move, TCAPS.nb_read - TCAPS.nb_move);
	else
		new = NULL;
	free(e->line);
	e->line = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
}
