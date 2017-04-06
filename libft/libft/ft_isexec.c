/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 20:09:52 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/06 14:55:02 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>

int			ft_isexec(char *path)
{
	struct stat	buf;

	ft_bzero(&buf, sizeof(struct stat));
	lstat(path, &buf);
	if (S_ISREG(buf.st_mode) && (S_IXUSR & buf.st_mode))
		return (1);
	return (0);
}
