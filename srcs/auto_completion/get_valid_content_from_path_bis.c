/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_content_from_path_bis.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:10:07 by aleghmar          #+#    #+#             */
/*   Updated: 2017/05/08 21:47:45 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		test_file(char *curr_path, char *curr_file, int exec_only)
{
	int			ret;
	struct stat	file_stat;
	char		*path;
	char		*tmp;

	ret = 0;
	tmp = ft_strjoin(curr_path, "/");
	path = ft_strjoin(tmp, curr_file);
	stat(path, &file_stat);
	if ((!exec_only || S_ISDIR(file_stat.st_mode))
			&& ft_strcmp(tmp, ".") && ft_strcmp(tmp, ".."))
		ret = 1;
	else if (exec_only && !access(path, X_OK))
		ret = 1;
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (ret);
}

void		ft_add_list(t_list **first, t_list **ptr, char *str)
{
	if (!*first)
	{
		*first = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = *first;
	}
	else
	{
		(*ptr)->next = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = (*ptr)->next;
	}
}

int			ft_countchar(char *str, char c)
{
	int i;

	i = 0;
	while (str && *str)
	{
		if (*str == c)
			++i;
		++str;
	}
	return (i);
}

int			ft_countstr(char *str, char *cmp)
{
	int i;
	int len;
	int len_ref;

	i = 0;
	len = 0;
	len_ref = ft_strlen(cmp);
	while (str && *str && cmp && *cmp)
	{
		if (!ft_strncmp(str, cmp, len_ref))
		{
			len = len_ref;
			++i;
		}
		while (--len > 0)
			str += !!*str;
		str += !!*str;
	}
	return (i);
}
