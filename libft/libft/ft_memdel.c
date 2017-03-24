/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:53:09 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:38:58 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	DESCRIPTION:
**     Takes as a parameter the address of a memory area that needs
**     to be freed with free(3), then puts the pointer to NULL.
*/

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
