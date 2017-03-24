/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:05:01 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:54:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Sets every character of the string to the value ’\0’
*/

void	ft_strclr(char *s)
{
	if (s)
		while (*s)
		{
			*s = '\0';
			++s;
		}
}
