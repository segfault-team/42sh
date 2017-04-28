/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_logic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:24 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:07:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Splits the command based on logical operators.
**	It fills a chained list, which holds the command and
**	the logical operator associated.
**	The first command have a l.op. of -42.
**		ex:   $> true && echo LOL
**		-->		{true, -42} -> {echo LOL, AND}
*/

static int		ft_split_logic_bis(t_logic *x, char **cmd,
		t_logic *ptr, int op)
{
	int			ret;
	char		**tmp;
	int			i;

	i = 0;
	while (cmd[++i])
	{
		if ((ret = ft_check_op(cmd[i])))
			op = ret;
		else
		{
			if (op)
			{
				ptr->next = ft_new_logic();
				ptr = ptr->next;
				ptr->op = op;
				op = 0;
			}
			if ((tmp = ft_tabcat(ptr->atom, cmd[i])) == NULL)
				return (ft_freelogic(x));
			ft_tabfree(ptr->atom);
			ptr->atom = tmp;
		}
	}
	return (0);
}

t_logic			*ft_split_logic(t_logic *x, char **cmd)
{
	t_logic		*ptr;

	if ((x = ft_new_logic()) == NULL)
		return (NULL);
	ptr = x;
	x->atom = ft_tabcat(NULL, cmd[0]);
	x->op = -42;
	if (ft_split_logic_bis(x, cmd, ptr, 0) < 0)
		return (NULL);
	return (x);
}
