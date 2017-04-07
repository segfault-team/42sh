/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_cut_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:02 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:02 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ctrl_k_loop(t_env *e, int i)
{
	xputs(TGETSTR_CE);
	if (i && (i % (WIN_WIDTH - 1) == 0))
	{
		xputs(TGETSTR_DW);
		xputs(TGETSTR_CR);
	}
	else
		xputs(TGETSTR_ND);
}

static void	tcaps_ctrl_k(t_env *e)
{
	int		i;
	char	*tmp;

	if (NB_MOVE >= (int)ft_strlen(e->line))
		return ;
	strfree(&e->cut);
	e->cut = ft_strdup(&e->line[NB_MOVE]);
	i = NB_MOVE;
	tmp = ft_strsub(e->line, 0, NB_MOVE);
	strfree(&e->line);
	e->line = tmp;
	xputs(TGETSTR_SC);
	xputs(TGETSTR_DM);
	while (i++ <= NB_READ)
		ctrl_k_loop(e, i);
	xputs(TGETSTR_ED);
	xputs(TGETSTR_RC);
	NB_READ -= (int)ft_strlen(e->cut);
}

static void	tcaps_ctrl_p(t_env *e, int cut_len, int tmp)
{
	xputs(TGETSTR_VI);
	cut_len = (int)ft_strlen(e->cut);
	ft_realloc_insert_str(e, e->cut);
	xputs(TGETSTR_DM);
	tmp = NB_READ;
	while (--tmp + ((int)ft_strlen(e->prompt) + 1) > 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_CE);
	}
	NB_READ = (int)ft_strlen(e->line);
	tmp = NB_READ - (NB_MOVE + cut_len);
	xputs(TGETSTR_CR);
	ft_prompt(e->prompt);
	ft_putstr(e->line);
	NB_MOVE = NB_READ;
	while (tmp--)
	{
		xputs(TGETSTR_LE);
		--NB_MOVE;
	}
	tcaps_recalc_pos(e);
	xputs(TGETSTR_VE);
}

static void	tcaps_check_ctrl_p(t_env *e)
{
	if (e->cut)
		tcaps_ctrl_p(e, 0, 0);
}

/*
** CTRL_K== 11
** CTRL_P== 16
*/

void		tcaps_cut_paste(t_env *e)
{
	if (BUF[0] == CTRL_K && NB_READ)
		tcaps_ctrl_k(e);
	else if (BUF[0] == CTRL_P)
		tcaps_check_ctrl_p(e);
}
