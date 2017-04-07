/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:56 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:56 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  INSTRUCTION FOR "Ctrl + l" KEYS
**
**  cl: clear active window
**  To do : reset positions after clear && check buffer after ctrl+l
*/

void	tcaps_clear(t_env *e)
{
	xputs(TGETSTR_CL);
	ft_prompt(e->prompt);
	ft_printf("%s", e->line);
}
