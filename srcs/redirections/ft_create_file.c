/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:49 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:49 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	create_aggre_file(t_env *e, int i)
{
	char	*file;
	int		ret;
	int		j;
	int		k;

	j = 1;
	k = -1;
	file = NULL;
	if (space_after_aggre(e->magic[i].cmd))
		return (open(e->magic[i + 1].cmd, O_CREAT | O_TRUNC, OFLAGS));
	while (j && (e->magic[i].cmd[j] != '&' || e->magic[i].cmd[j - 1] != '>'))
		++j;
	file = ft_strnew((int)ft_strlen(e->magic[i].cmd) - j);
	while (e->magic[i].cmd[++j])
		file[++k] = e->magic[i].cmd[j];
	if (is_only_numbers(file))
	{
		strfree(&file);
		return (-1);
	}
	ret = open(file, O_CREAT | O_TRUNC, OFLAGS);
	strfree(&file);
	return (ret);
}

static char	*isolate_file(t_env *e, int i)
{
	int	pos;

	pos = (int)ft_strlen(e->magic[i].cmd) - 1;
	while (--pos && e->magic[i].cmd[pos] != '>')
		;
	if (pos)
		return (&e->magic[i].cmd[pos + 1]);
	return (NULL);
}

int			space_after_aggre(char *s)
{
	int	i;

	i = (int)ft_strlen(s) - 1;
	if (s[i] == '&' && s[i - 1] == '>')
		return (1);
	return (0);
}

void		ft_create_file(t_env *e)
{
	int		i;
	int		fd;

	i = -1;
	fd = -1;
	while (e->magic[++i].type)
	{
		if (!ft_strcmp(e->magic[i].type, "output") || is_special_aggre(e, i))
		{
			if (i && !ft_strcmp(e->magic[i - 1].cmd, ">"))
				fd = open(e->magic[i].cmd, O_CREAT | O_TRUNC, OFLAGS);
			else if (is_special_aggre(e, i))
				fd = open(isolate_file(e, i), O_CREAT, OFLAGS);
			else
				fd = open(e->magic[i].cmd, O_CREAT, OFLAGS);
			ft_close(fd);
		}
		else if (ft_strstr(e->magic[i].cmd, ">&"))
		{
			fd = create_aggre_file(e, i);
			if (fd != -1)
				ft_close(fd);
		}
	}
}
