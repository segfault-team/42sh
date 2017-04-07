/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:04 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	insert_char(t_env *e, char c, int pos)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	if (!(new = ft_strnew((int)ft_strlen(e->line) + 1)))
		return ;
	while (e->line[++i])
	{
		if (++j == pos)
			new[j++] = c;
		new[j] = e->line[i];
	}
	new[++j] = '\0';
	strfree(&e->line);
	e->line = new;
}
