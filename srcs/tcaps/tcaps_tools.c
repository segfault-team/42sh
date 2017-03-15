/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:28:29 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/13 15:32:07 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	dsh_putchar(int c)
{
	return (ft_putchar(c));
}

/*
** RAZ LE BOL DE TOUT REECRIRE !
*/

void	xputs(char *tcaps)
{
//	char	*res;

//	res = tgetstr(tag, NULL);
	ft_putstr(tcaps);
//	tputs(tcaps, 1, dsh_putchar);
}

void	move_right(t_env *e)
{
	if (TCAPS.nb_col == (WIN_WIDTH - 1))
	{
		xputs(TGETSTR_DW);
		xputs(TGETSTR_CR);
	}
	else
		xputs(TGETSTR_ND);
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}
