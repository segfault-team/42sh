/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:28 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:28 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  INSTRUCTION FOR ALL INSERTION
**		OF VISIBLE CHAR
**
**  im: start insert mode
**  ei: end insert mode
*/

void	tcaps_insert(t_env *e)
{
	xputs(TGETSTR_IM);
	tputs(&BUF[0], 1, dsh_putchar);
	xputs(TGETSTR_EI);
	tcaps_recalc_pos(e);
}
