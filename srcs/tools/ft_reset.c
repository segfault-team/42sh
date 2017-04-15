/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:26 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:26 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_hdoc_list(t_env *e)
{
	t_list	*tmp;

	e->hdoc = e->b_hdoc;
	while (e->hdoc)
	{
		tmp = e->hdoc->next;
		ft_free_tab(e->hdoc->content);
		e->hdoc->content = NULL;
		free(e->hdoc);
		e->hdoc = NULL;
		e->hdoc = tmp;
	}
	e->b_hdoc = NULL;
}

int			ft_reset_line(t_env *e)
{
	if (e->raw)
		e->raw -= 1;
	strfree(&e->line);
	strfree(&e->line_bkp);
	strfree(&MULTI);
	free_hdoc_list(e);
	NB_MOVE = 0;
	NB_READ = 0;
	HIST_MOVE = -1;
	e->check_ctrl_c = 0;
	e->hdoc_nb = 0;
	e->quote = '\0';
	e->multi_quote = '\0';
	e->env_exec = 0;
	NB_COL = 0;
	NB_LINE = 0;
	return (0);
}
