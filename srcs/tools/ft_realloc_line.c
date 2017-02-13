/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/13 18:15:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char    *ft_realloc_delete_char(t_env *e, int pos)
{
	char    *new;
	int     len;
	int     i;
	int		j;

	if (e->line)
		len = TCAPS.nb_read;
	else
		len = 1;
	if ((new = ft_strnew(sizeof(char) * (len))) == NULL)
		return (NULL);
	i = 0;
	j = -1;
	if (len != 1)
		while (e->line[i])
		{
			if (i != pos)
				new[++j] = e->line[i++];
			else
				++i;
		}
	else if (TCAPS.nb_read == 1)
		new[0] = '\0';
	ft_free_line(e);
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
	ft_free_line(e);
	return (new);
}
