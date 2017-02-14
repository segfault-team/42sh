/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:53:42 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/22 15:21:43 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_init_gnl(t_gnl **save)
{
	if (((*save) = malloc(sizeof(t_gnl))) == NULL)
		return (-1);
	(*save)->rline = NULL;
	return (0);
}

static int	ft_copy_rline(char **line, t_gnl **save)
{
	char	*ptr;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	ptr = NULL;
	if ((ptr = ft_strchr((*save)->rline, '\n')))
	{
		tmp = ft_strndup((*save)->rline, (int)(ptr - (*save)->rline));
		if (ft_strlen(++ptr))
			tmp2 = ft_strdup(ptr);
	}
	else
		tmp = ft_strdup((*save)->rline);
	free((*save)->rline);
	if (tmp2)
		(*save)->rline = tmp2;
	else
		(*save)->rline = NULL;
	*line = tmp;
	if ((*save)->rline)
		return (1);
	return (0);
}

static int	ft_join_end_line(char **line, t_gnl **save, char *buff)
{
	char	*ptr;
	char	*tmp;
	char	*tmp2;

	if ((ptr = ft_strchr(buff, '\n')))
	{
		tmp2 = ft_strndup(buff, (int)(ptr - buff));
		tmp = ft_strjoin(*line, tmp2);
		if (ft_strlen(++ptr))
			(*save)->rline = ft_strdup(ptr);
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
	static t_gnl	*save = NULL;
	char			buff[BUFF_SIZE + 1];
	char			*ptr;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (save == NULL && ft_init_gnl(&save) < 0)
		return (-1);
	if (save->rline && ft_copy_rline(line, &save))
		return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		ptr = buff;
		if (ft_join_end_line(line, &save, ptr))
			break ;
	}
	return ((ret > 0 || *line) ? 1 : ret);
}
