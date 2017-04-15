/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:31 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:31 by lfabbro          ###   ########.fr       */
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
		strfree(&e->line);
		if (e->hdoc_words)
		{
			ft_free_tab(e->hdoc_words);
			e->hdoc_words = NULL;
		}
		strfree(&MULTI);
		HIST_MOVE = -1;
		ft_putstr("\n\n");
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
