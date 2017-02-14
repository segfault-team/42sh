/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 19:58:35 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/20 17:06:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_error(char *util, char *msg, char *what)
{
	if (what)
		ft_printfd(2, "%s: %s %s\n", util, msg, what);
	else if (util)
		ft_printfd(2, "%s: %s\n", util, msg);
	else
		ft_printfd(2, "%s\n", msg);
	return (-1);
}
