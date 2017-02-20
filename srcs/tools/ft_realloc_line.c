/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/16 11:31:19 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char    *ft_realloc_delete_char(t_env *e)
{
	char    *new;
	int     len;
	int     i;
	int		j;

	if (e->line)
		len = TCAPS.nb_read;
	else
		len = 1;
	if (!(new = ft_strnew(sizeof(char) * (len))))
		return (NULL);
	i = 0;
	j = -1;
	if (len > 1)
		while (e->line[i])
		{
			if (i != TCAPS.nb_move - 1)
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
**	COPY OLD IN NEW AND INSERT
**	CHAR C AT THE INDEX DEFINE
*/

char    *ft_realloc_insert_char(t_env *e, char c)
{
	char    *new;
	int     len;
	int     i;
	int		j;

	if (e->line)
		len = ft_strlen(e->line) + 1;
	else
		len = 1;
	if ((new = ft_strnew(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	j = -1;
	if (len != 1)
		while (e->line[i])
		{
			if (i != TCAPS.nb_move || !c)
				new[++j] = e->line[i++];
			else
			{
				new[++j] = c;
				c = '\0';
			}
		}
	strfree(&e->line);
	return (new);
}

void	ft_realloc_insert_str(t_env *e, char *str)
{
	char	*new;
	char	*tmp;

	new = ft_strsub(e->line, 0, TCAPS.nb_move);
	tmp = ft_strjoin(new, str);
	strfree(&new);
	new = ft_strsub(e->line, TCAPS.nb_move, TCAPS.nb_read - TCAPS.nb_move);
	free(e->line);
	e->line = ft_strjoin(tmp, new);
	strfree(&tmp);
	strfree(&new);
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
	if ((new = ft_strnew(sizeof(char) * (len + 1))) == NULL)
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
