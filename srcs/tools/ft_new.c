/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:24 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:31:44 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job		*ft_new_job(t_job *next, int pid)
{
	t_job	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = next;
	new->pid = pid;
	return (new);
}
