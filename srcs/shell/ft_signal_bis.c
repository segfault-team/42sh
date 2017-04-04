/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:31:41 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/04 15:34:13 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_sigint_reset(t_env *e)
{
	if (!e->child_running)
	{
		tcaps_ctrl_end(e);
		e->hdoc_nb = 0;
		strfree(&e->herestock);
		if (e->hdoc_words)
		{
			ft_free_tab(e->hdoc_words);
			e->hdoc_words = NULL;
		}
		strfree(&MULTI);
		TCAPS.hist_move = -1;
		ft_putchar('\n');
		strfree(&e->prompt);
		e->prompt = ft_create_prompt(e, STD_PROMPT);
		ft_prompt(e->prompt);
	}
}

void		ft_sigint(t_env *e)
{
	e->check_ctrl_c = 1;
	if (e->c_match)
	{
		e->check_ctrl_c = 0;
		e->selected = -42;
		print_auto_completion(e, NULL, NULL, NULL);
		xputs(e->struct_tputs.cd);
		valid_selection(e);
	}
	ft_sigint_reset(e);
}
