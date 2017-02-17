/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:02:48 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:41:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Outputs the string s to the standard output followed by a ’\n’.
*/

void	ft_putendl(char const *s)
{
	if (s)
	{
		ft_putstr(s);
		ft_putchar('\n');
	}
}
