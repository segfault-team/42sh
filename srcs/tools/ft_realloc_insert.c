/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:24:08 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/20 20:45:05 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (e->line)
	{
		free(e->line);
		e->line = NULL;
		}
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
	// nb_move += cut
	// nb_read = e->line;
}
