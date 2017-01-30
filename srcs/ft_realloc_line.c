/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/30 17:00:42 by kboddez          ###   ########.fr       */
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
		len = TCAPS.nb_read;//ft_strlen(e->line) + 1;
	else
		len = 1;
	if ((new = ft_strnew(sizeof(char) * (len))) == NULL)
		return (NULL);
	i = 0;
	j = -1;
	if (len != 1)
		while (e->line[i])
		{
			if (i != TCAPS.nb_move - 1)
				new[++j] = e->line[i++];
			else
				++i;
		}
	else if (TCAPS.nb_read == 1)
		new[0] = '\0';
	if (e->line)
	{
		free(e->line);
		e->line = NULL;
	}
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
			if (i != TCAPS.nb_move - (int)ft_strlen(e->prompt) || !c)
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
	{
		free(e->line);
		e->line = NULL;
	}
	return (new);
}
