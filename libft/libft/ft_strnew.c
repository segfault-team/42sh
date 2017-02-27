/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:57:06 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/27 12:54:06 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a “fresh” string ending
**     with ’\0’. Each character of the string is initialized at
**     ’\0’. If the allocation fails the function returns NULL.
*/

char	*ft_strnew(size_t size)
{
	char	*new;

	if (!size || (new = malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
