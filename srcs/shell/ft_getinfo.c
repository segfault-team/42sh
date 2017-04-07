/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getinfo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:26 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:26 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*ft_getpath_uid(int uid, char *path)
{
	char	*line;
	char	**row;
	char	*s_uid;
	int		fd;

	if ((fd = open("/etc/passwd", O_RDONLY)) == -1)
		return (NULL);
	s_uid = ft_itoa(uid);
	row = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strchr(line, ':') && !ft_strncmp(ft_strchr(
						ft_strchr(line, ':'), ':'), s_uid, ft_strlen(s_uid)))
		{
			row = ft_strsplit(line, ':');
			path = ft_strdup(row[5]);
			break ;
		}
		strfree(&line);
	}
	ft_tabfree(row);
	strfree(&s_uid);
	close(fd);
	return (path);
}

char		*ft_getpath_login(char *login)
{
	char	*path;
	char	*line;
	char	**row;
	int		fd;

	if ((fd = open("/etc/passwd", O_RDONLY)) == -1)
		return (NULL);
	path = NULL;
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp(line, login, ft_strlen(login)) && ft_strchr(line, ':'))
		{
			if ((row = ft_strsplit(line, ':')) && row[5])
				path = ft_strdup(row[5]);
			ft_tabfree(row);
			strfree(&line);
			close(fd);
			return (path);
		}
		strfree(&line);
	}
	close(fd);
	return (NULL);
}
