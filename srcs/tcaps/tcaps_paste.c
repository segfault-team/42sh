/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_paste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:29 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:29 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		is_print(char c)
{
	return ((c >= ' ' && c <= '~') || c == '\n');
}

int				is_paste(char *buf)
{
	if (buf && (buf[0] || buf[1] || buf[2]))
		if (is_print(buf[0]) && is_print(buf[1]) && (is_print(buf[2])
					|| buf[2] == 0))
			return (1);
	return (0);
}

int				tcaps_paste(t_env *e, char *buf)
{
	int		i;

	i = -1;
	xputs(TGETSTR_IM);
	while (buf[++i] && i < 3)
	{
		if (is_print(buf[i]))
		{
			ft_putchar_fd(buf[i], 1);
			if (i > 0 || buf[i] == '\n')
			{
				if (NB_READ == NB_MOVE)
					e->line = ft_realloc_line(e, buf[i]);
				else
					e->line = ft_realloc_insert_char(e, buf[i]);
				++NB_MOVE;
				++NB_READ;
			}
		}
	}
	xputs(TGETSTR_EI);
	tcaps_recalc_pos(e);
	return (i);
}
