/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:41:05 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/25 18:27:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabdup(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	if ((dup = ft_tabnew(ft_tablen(tab))) == NULL)
		return (NULL);
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		++i;
	}
	dup[i] = NULL;
	return (dup);
}
