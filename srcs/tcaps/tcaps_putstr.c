/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:31 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:31 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  sc: save position curosr
**  cr: carriage return (debut de ligne)
**  dm: start delete mode
**  le: left
**  dc: delete one char
**  dl: delete line
**  ce: delete line from cursor
**  ed: end delete mode
**  rc: recover cursor position
*/

int		tcaps_putstr(t_env *e, char *str)
{
	int		len;
	int		pos;

	xputs(TGETSTR_DM);
	len = NB_MOVE + (int)ft_strlen(e->prompt);
	pos = NB_READ;
	while (len-- > 0)
		xputs(TGETSTR_LE);
	xputs(TGETSTR_CD);
	xputs(TGETSTR_ED);
	ft_prompt(e->prompt);
	tcaps_recalc_pos(e);
	if (str)
	{
		ft_putstr(str);
		while (pos-- > NB_MOVE)
			xputs(TGETSTR_LE);
		tcaps_recalc_pos(e);
		if (NB_COL == (WIN_WIDTH - 1))
			xputs(TGETSTR_ND);
	}
	return (0);
}
