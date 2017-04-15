/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:22 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_error2(char *msg, char *msg2, char *msg3, char *msg4)
{
	ft_printfd(2, "%s: %s %s: %s\n", msg, msg2, msg3, msg4);
	return (-1);
}

int		ft_error(char *util, char *msg, char *what)
{
	if (what && util && msg)
		ft_printfd(2, "%s: %s: %s: %s\n", SH_NAME, util, msg, what);
	else if (util && msg)
		ft_printfd(2, "%s: %s: %s\n", SH_NAME, util, msg);
	else if (msg)
		ft_printfd(2, "%s: %s\n", SH_NAME, msg);
	return (-1);
}
