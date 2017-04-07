/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:13 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:13 by lfabbro          ###   ########.fr       */
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

	xputs(TGETSTR_SC);
	xputs(TGETSTR_CR);
	xputs(TGETSTR_DM);
	len = NB_READ;
	while (--len > 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_DC);
	}
	xputs(TGETSTR_DL);
	xputs(TGETSTR_CE);
	xputs(TGETSTR_ED);
	ft_prompt(e->prompt);
	tputs(str, 1, dsh_putchar);
	xputs(TGETSTR_RC);
	return (0);
}
