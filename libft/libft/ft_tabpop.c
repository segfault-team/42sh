/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:46:56 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 16:55:37 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabpop(char **tab, size_t pop)
{
	char	**new;
	size_t	len;
	size_t	i;

	new = NULL;
	len = ft_tablen(tab);
	len += (len == 1) ? 1 : 0;
	i = -1;
	if (tab && len && pop < len)
	{
		new = ft_tabnew(len - 1);
		while (++i < pop && tab[i])
		{
			new[i] = ft_strdup(tab[i]);
		}
		while (tab[++i])
		{
			new[i - 1] = ft_strdup(tab[i]);
		}
		new[i - 1] = NULL;
	}
	return (new);
}
