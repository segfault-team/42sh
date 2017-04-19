/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 12:27:46 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/17 17:25:59 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	INSTRUCTION FOR ALL KEY
**	WITH PRINTABLE CHAR
*/

static void	tcaps_del_prompt(t_env *e)
{
	int		len;

	len = (int)ft_strlen(e->prompt);
	while (len-- >= 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_CE);
	}
}

static void	midline_insert(t_env *e, int s_move, int len)
{
	e->line = ft_realloc_insert_char(e, BUF[0]);
	xputs(TGETSTR_DM);
	while (--len > 0)
	{
		xputs(TGETSTR_LE);
		xputs(TGETSTR_CE);
	}
	if (!e->raw)
	{
		tcaps_del_prompt(e);
		ft_prompt(e->prompt);
		s_move += ft_putstr(e->line);
	}
	while (s_move-- > NB_MOVE)
		xputs(TGETSTR_LE);
	tcaps_recalc_pos(e);
	if (TCAPS.nb_col == (WIN_WIDTH - 1))
	{
		xputs(TGETSTR_DW);
		xputs(TGETSTR_CR);
	}
	else
		xputs(TGETSTR_ND);
}

void		tcaps_manage_printable_char(t_env *e)
{
	int		len;
	int		s_move;

	s_move = 0;
	len = NB_READ;
	if (NB_MOVE == NB_READ)
		e->line = ft_realloc_line(e, BUF[0]);
	else
		midline_insert(e, s_move, len);
	++NB_MOVE;
	++NB_READ;
}

static int	ft_check_fd_in()
{
	/*if (!isatty(STDIN_FILENO))
	{
		ft_printfd(2, "Input fd is not a tty. Abort.\n");
		return (0);
	}*/
	return (1);
}

/*
** for now we handle ctrl-z, later on we will get rid of that
*/

int			main(int ac, char **av, char **env)
{
	t_env	*e;
	int		ret;

	if ((e = (t_env *)malloc(sizeof(t_env))) == NULL ||
			!ft_check_fd_in())
		return (-1);
	env_access(e);
	(void)ac;
	(void)av;
	e->raw = ft_init(e, env);
	ft_set_sig_handler();
	if (!e->raw)
		ft_prompt(e->prompt);
	while (e->x)
	{
		read_input(e);
		reading(e);
	}
	tcaps_reset(e);
	ft_write_history(e, O_TRUNC);
	ret = e->exit;
	if (!e->raw)
		ft_putendl("exit");
	ft_env_free(e);
	return (ret);
}
