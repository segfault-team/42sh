/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 18:21:35 by aleghmar          #+#    #+#             */
/*   Updated: 2014/11/18 14:58:18 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*frais;
	void	*tmp;

	tmp = NULL;
	if (content != NULL)
	{
		tmp = (void *)malloc(content_size);
		ft_bzero(tmp, content_size);
		if (content_size > 0)
			tmp = ft_memcpy(tmp, content, content_size);
	}
	frais = (t_list *)malloc(sizeof(t_list));
	if (frais)
	{
		frais->content = tmp;
		if (tmp == NULL)
			frais->content_size = 0;
		else
			frais->content_size = content_size;
		frais->next = NULL;
		return (frais);
	}
	return (NULL);
}
