/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:53:45 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 13:16:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Outputs the character c to the standard output.
**     Returns the number of printed chars (1).
*/

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
