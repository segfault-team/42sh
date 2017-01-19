/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issticky.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:26:21 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/29 17:27:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>

int			ft_issticky(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) == -1)
		return (0);
	if ((buf.st_mode & S_ISUID) || (buf.st_mode & S_ISGID))
		return (1);
	return (0);
}
