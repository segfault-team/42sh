/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:25:35 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 11:26:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a “fresh” link. The
**     variables content and content_size of the new link are initialized
**     by copy of the parameters of the function. If the parameter
**     content is nul, the variable content is initialized to
**     NULL and the variable content_size is initialized to 0 even
**     if the parameter content_size isn’t. The variable next is
**     initialized to NULL. If the allocation fails, the function returns
**     NULL.
*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_list;

	if ((new_list = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content)
	{
		(*new_list).content = NULL;
		(*new_list).content_size = 0;
		(*new_list).next = NULL;
		return (new_list);
	}
	(*new_list).content = (void *)malloc(sizeof(*content) * \
			ft_strlen((const char *)content));
	ft_memmove((void *)(*new_list).content, content, content_size);
	(*new_list).content_size = content_size;
	(*new_list).next = NULL;
	return (new_list);
}
