/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:59:28 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/29 15:06:12 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t		ft_nwords(char const *str, char div)
{
	int		i;
	size_t	nwds;

	i = 0;
	nwds = 0;
	if (str)
	{
		while (str[++i] != '\0')
		{
			if (str[i] != div && str[i - 1] == div)
				++nwds;
		}
		if (!str[i] && i > 0 && str[i - 1] != div)
			++nwds;
	}
	return (nwds);
}

size_t		ft_wordlen(char const *str, char div)
{
	size_t	wlen;

	wlen = 0;
	while (str[wlen] != '\0' && str[wlen] != div)
		++wlen;
	return (wlen);
}

char		**ft_strsplit(char const *str, char div)
{
	char	**tab;
	size_t	nwords;
	size_t	wlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nwords = ft_nwords(str, div);
	if (nwords == 0 || (tab = ft_tabnew(nwords)) == NULL)
		return (NULL);
	while (i < (int)ft_strlen(str))
	{
		if ((wlen = ft_wordlen(&str[i], div)))
		{
			if ((tab[j] = ft_strndup(&str[i], wlen)) == NULL)
				break ;
			i += wlen;
			++j;
			tab[j] = NULL;
		}
		else
			++i;
	}
	return (tab);
}
