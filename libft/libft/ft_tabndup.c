/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:48:35 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/24 17:03:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabndup(char **tab, size_t b)
{
	char	**dup;
	size_t	len;
	size_t	i;

	if ((dup = ft_tabnew(b)) == NULL)
		return (NULL);
	i = 0;
	len = ft_tablen(tab);
	while (i < b && i < len)
	{
		dup[i] = ft_strdup(tab[i]);
		++i;
	}
	dup[i] = NULL;
	return (dup);
}
