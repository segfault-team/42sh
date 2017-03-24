/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:02:08 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:52:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Takes as a parameter the address of a string that need to be
**     freed with free(3), then sets its pointer to NULL.
*/

void	ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}
