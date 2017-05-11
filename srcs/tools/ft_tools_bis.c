/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:01:54 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/11 14:01:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_dir(char *str)
{
	struct stat		info;

	ft_bzero(&info, sizeof(struct stat));
	if (!str || lstat(str, &info) < 0)
		return (-1);
	return (S_ISDIR(info.st_mode));
}
