/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:53:42 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 13:26:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_copy_rline(char **line, char **rline)
{
	char	*ptr;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	ptr = NULL;
	if ((ptr = ft_strchr(*rline, '\n')))
	{
		tmp = ft_strndup(*rline, (int)(ptr - *rline));
		if (ft_strlen(ptr + 1))
			tmp2 = ft_strdup(ptr + 1);
	}
	else
		tmp = ft_strdup(*rline);
	free(*rline);
	if (tmp2)
		*rline = tmp2;
	else
		*rline = NULL;
	*line = tmp;
	if (*rline || ptr)
		return (1);
	return (0);
}

static int	ft_join_end_line(char **line, char **rline, char *buff)
{
	char	*ptr;
	char	*tmp;
	char	*tmp2;

	if ((ptr = ft_strchr(buff, '\n')))
	{
		tmp2 = ft_strndup(buff, (int)(ptr - buff));
		tmp = ft_strjoin(*line, tmp2);
		if (ft_strlen(++ptr))
			*rline = ft_strdup(ptr);
		free(tmp2);
	}
	else
		tmp = ft_strjoin(*line, buff);
	if (*line)
		free(*line);
	*line = tmp;
	if (ptr)
		return (1);
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char		*rline = NULL;
	char			buff[BUFF_SIZE + 1];
	char			*ptr;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (rline && ft_copy_rline(line, &rline))
		return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = buff;
		if (ft_join_end_line(line, &rline, ptr))
			break ;
	}
	return ((ret > 0 || *line) ? 1 : ret);
}
