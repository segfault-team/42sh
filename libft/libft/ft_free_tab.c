/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 18:57:53 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/09 14:21:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabfree(char **tab)
{
	ft_free_tab(tab);
}

void		ft_free_tab(char **tab)
{
	int		i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i] != NULL)
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
		tab = NULL;
	}
}
