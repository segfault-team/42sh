/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:49:07 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/24 19:03:33 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_reset_line(t_env *e)
{
	if (e->line)
		strfree(&e->line);
	e->tcaps.nb_move = 0;
	e->tcaps.nb_read = 0;
//	ft_bzero(e->buf, 3);
//	ft_putchar('\n');
//	ft_prompt(e->prompt);
	return (0);
}
