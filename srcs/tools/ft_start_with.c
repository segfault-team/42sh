/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_with.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:09:51 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:09:51 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_start_with(char *str, char *comp)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	if (!comp)
		return (1);
	if (ft_strlen(str) < ft_strlen(comp))
		return (0);
	while (comp[++i])
	{
		if (comp[i] != str[i])
			return (0);
	}
	return (1);
}
