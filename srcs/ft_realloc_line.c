	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:30:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/02 13:50:05 by vlistrat         ###   ########.fr       */
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
	new = ft_strsub(e->line, TCAPS.nb_move, TCAPS.nb_read - TCAPS.nb_move);
	free(e->line);
	e->line = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
	// nb_move += cut
	// nb_read = e->line;
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

/*
**	sc: save position curosr
**	cr: carriage return (debut de ligne)
**	dm: start delete mode
**	le: left
**	dc: delete one char
**	dl: delete line
**	ce: delete line from cursor
**	ed: end delete mode
**	rc: recover cursor position
*/

int		tcaps_putstr(t_env *e, char *str)
{
	int		l;
//	int		i;

//	i = -1;
	xputs("sc");
	xputs("cr");
	xputs("dm");
	l = TCAPS.nb_read;
	while (--l > 0)
	{
		xputs("le");
		xputs("dc");
	}
	xputs("dl");
	xputs("ce");
	xputs("ed");
	tputs(e->prompt, 1, dsh_putchar);
	tputs(str, 1, dsh_putchar);
	xputs("rc");
	return (0);
}

