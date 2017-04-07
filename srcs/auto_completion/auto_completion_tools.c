/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:28:22 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:28:22 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_is_dir(char *target)
{
	struct stat	s;
	int			ret;

	ret = 0;
	if (stat(target, &s) != -1)
	{
		if (S_ISDIR(s.st_mode))
			ret = 1;
	}
	return (ret);
}
