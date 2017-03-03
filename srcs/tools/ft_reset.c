/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:49:07 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/03 16:01:02 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_reset_line(t_env *e)
{
	strfree(&e->line);
	strfree(&e->line_bkp);
	strfree(&MULTI);
	e->tcaps.nb_move = 0;
	e->tcaps.nb_read = 0;
	TCAPS.hist_move = -1;
//	ft_bzero(e->buf, 3);
//	ft_putchar('\n');
//	ft_prompt(e->prompt);
	e->check_ctrl_c = 0;
	return (0);
}
