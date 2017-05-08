/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:59:09 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/08 23:43:04 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_last_is_builtin(t_env *e, int i)
{
	if (ft_is_builtin(e->cat[i][0]) && !e->env_exec)
		e->last_is_builtin = 1;
	return (0);
}

t_job		*ft_new_job(t_job *next, int pid)
{
	t_job	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = next;
	new->pid = pid;
	return (new);
}
