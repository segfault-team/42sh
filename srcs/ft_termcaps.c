/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <kboddez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 13:34:34 by kboddez           #+#    #+#             */
/*   Updated: 2017/01/28 14:01:47 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		dsh_putchar(int c)
{
	char	d;

	d = c;
	return (write(1, &d, 1));
}

int 	ft_termcaps(t_env *e)
{
	if (!check_key(BUF, 27, 91, 65) &&
		!check_key(BUF, 27, 91, 66))
		TCAPS.hist_move = -1;
	if (BUF[0] == 4)
		ft_exit(e);
	else if (check_read(BUF))
		inst_term_insert(e);
	else if (check_key(BUF, 12, 0, 0))
		inst_term_clear(e);
	else if (check_key(BUF, 1, 0, 0))
		inst_term_rtrbeg(e);
	else if (check_key(BUF, 27, 91, 65) ||
			 check_key(BUF, 27, 91, 66))
		inst_term_history(e);
	else if (check_key(BUF, 27, 91, 67) && TCAPS.nb_move < TCAPS.nb_read)
		inst_term_right(e);
	else if (check_key(BUF, 27, 91, 68) && TCAPS.nb_move > 0)
		inst_term_left(e);
	else if (BUF[0] == 127 && TCAPS.nb_read && TCAPS.nb_move)
		inst_term_del(e);
	else if (BUF[0])
		printf("\n%d | %d | %d\n", BUF[0], BUF[1], BUF[2]);
	return (0);
}
