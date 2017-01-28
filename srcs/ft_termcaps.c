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

int		term_history(int up);
//	void	print_pos(char *str);

int		dsh_putchar(int c)
{
	char	d;

	d = c;
	return (write(1, &d, 1));
}

int 	ft_termcaps(t_env *e)
{
	char	*res;
	int		up;

	res = NULL;
	up = 0;
	up = (check_key(BUF, 27, 91, 65)) ? up + 1: 0;
	if (BUF[0] == 4)
		ft_exit(e);
	else if (check_read(BUF))
	{
//im: start insert mode
//ei: end insert mode
		res = tgetstr("im", NULL);
		tputs(res, 1, dsh_putchar);
		tputs(&BUF[0], 1, dsh_putchar);
		res = tgetstr("ei", NULL);
		tputs(res, 1, dsh_putchar);
		++TCAPS.nb_move;
	}
	else if (check_key(BUF, 12, 0, 0))
	{
//cl: clear window
		res = tgetstr("cl", NULL);
		tputs(res, 1, dsh_putchar);
		ft_putstr(e->prompt);
	}
/*	else if (check_key(BUF, 27, 91, 65))
	{
		//cr: return at the begining of the line
		//cd: clear the line
		res = tgetstr("cr", NULL);
		id = tgetstr("cd", NULL);
		tputs(res, 1, dsh_putchar);
		tputs(id, 1, dsh_putchar);
		res = tgetstr("cm", NULL);
		print_pos("#> ", &wpos);
		tputs(tgoto(res, 3, wpos.y), 1, dsh_putchar);
		term_history(up, &wpos);
	}
*/	else if (check_key(BUF, 27, 91, 66))
		printf("down arrow\n");
	else if (check_key(BUF, 27, 91, 67) && TCAPS.nb_move < TCAPS.nb_read)
	{
//nd: move right char
//		ft_printf("%d | %d\n", TCAPS.nb_move, TCAPS.nb_read);
		res = tgetstr("nd", NULL);
		tputs(res, 1, dsh_putchar);
		++TCAPS.nb_move;
	}
	else if (check_key(BUF, 27, 91, 68) && TCAPS.nb_move > 0)
	{
		res = tgetstr("le", NULL);
		tputs(res, 1, dsh_putchar);
		--TCAPS.nb_move;
//		ft_printf("%d | %d\n", TCAPS.nb_move, TCAPS.nb_read);
	}
	else if (BUF[0] == 127 && TCAPS.nb_read && TCAPS.nb_move)
	{
// dm: start delete mode
// le : move left
// dc : delete char
// ed: end delete mode
//		printf("\nav: %d | %d\n", TCAPS.nb_move, TCAPS.nb_read);
//		printf("ap: %d | %d\n", TCAPS.nb_move, TCAPS.nb_read);
		--TCAPS.nb_read;
		res = tgetstr("dm", NULL);
		tputs(res, 1, dsh_putchar);
		res = tgetstr("le", NULL);
		tputs(res, 1, dsh_putchar);
		if (TCAPS.nb_move)
			--TCAPS.nb_move;
		res = tgetstr("dc", NULL);
		tputs(res, 1, dsh_putchar);
		res = tgetstr("ed", NULL);
		tputs(res, 1, dsh_putchar);
	}
//	else if (BUF[0])
//		printf("\n%d | %d | %d\n", BUF[0], BUF[1], BUF[2]);
	return (0);
}
