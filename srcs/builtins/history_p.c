/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:09:55 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:09:55 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	history_p(t_env *e, char **cmd)
{
	int		i;
	char	**tmp;

	i = 1;
	while (cmd[++i])
		ft_printf("%s\n", cmd[i]);
	tmp = e->history;
	e->history = delete_line_in_tab(e->history, (int)ft_tablen(e->history) - 1);
	ft_free_tab(tmp);
	return (1);
}
