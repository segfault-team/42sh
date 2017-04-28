/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:09:46 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:09:46 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*remove_spaces(char *str)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ret = NULL;
	len = 0;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			++len;
	i = -1;
	ret = ft_strnew(len);
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			ret[++j] = str[i];
	if (j < 1)
		return (NULL);
	return (ret);
}
