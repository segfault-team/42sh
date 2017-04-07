/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:22 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_last_char(t_env *e, char c)
{
	return (e->line && NB_READ >= 2 && e->line[NB_READ - 1] == c
			&& e->line[NB_READ - 2] != '\\');
}

int		check_prev_last_char(t_env *e, char c)
{
	return (e->line && NB_READ >= 2 && e->line[NB_READ - 2] == c
			&& e->line[NB_READ - 3] != '\\');
}
