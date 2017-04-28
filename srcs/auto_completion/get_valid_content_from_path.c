/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_content_from_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:10:06 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:10:06 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_start_with_bis(char *str, char *comp)
{
	int	i;

	i = -1;
	if (ft_strlen(str) < ft_strlen(comp))
		return (0);
	while (comp && comp[++i])
	{
		if (comp[i] && comp[i] != str[i])
			return (0);
	}
	if (str[0] == '.' && i <= 0)
		return (0);
	return (1);
}

char		*escape_specials(char *str, int i, int len)
{
	char	*tmp;
	char	*ret;
	int		k;

	k = ft_countchar(str, ' ') + ft_countchar(str, '	')
	+ ft_countchar(str, '\'') + ft_countchar(str, '\"');
	if (!str || !(tmp = ft_strnew((int)ft_strlen(str) + k + 1)))
		return (NULL);
	ret = tmp;
	ft_strncpy(tmp, str, i);
	str += i;
	tmp += i;
	while (str && tmp && *str && len--)
	{
		if (*str == ' ' || *str == '	' || *str == '\'' || *str == '\"')
		{
			*tmp = '\\';
			tmp++;
		}
		*tmp = *str;
		++tmp;
		++str;
	}
	ft_strcpy(tmp, str);
	return (ret);
}

int			cur_inquote(char *str, int pos)
{
	int s_quote;
	int d_quote;

	s_quote = 0;
	d_quote = 0;
	while (pos < (int)ft_strlen(str) && str[pos] && pos)
	{
		if (str[pos] == '\'' && !ft_is_escaped(str, pos))
			s_quote++;
		else if (str[pos] == '\"' && !ft_is_escaped(str, pos))
			d_quote++;
		pos--;
	}
	pos = 0;
	if (d_quote % 2)
		pos += 2;
	if (s_quote % 2)
		pos += 1;
	return (pos);
}

t_list		*dir_to_list(t_env *e, char *curr_path)
{
	DIR				*dir_id;
	struct dirent	*dir_entry;
	t_list			*first;
	t_list			*ptr;
	char			*tmp;

	first = NULL;
	if ((dir_id = opendir(curr_path)) == NULL)
		return (NULL);
	while ((dir_entry = readdir(dir_id)) != NULL)
	{
		if (!cur_inquote(e->line, NB_MOVE - 1))
			tmp = escape_specials(dir_entry->d_name, 0, -1);
		else
			tmp = ft_strdup(dir_entry->d_name);
		if (ft_strcmp(tmp, ".") && ft_strcmp(tmp, ".."))
			ft_add_list(&first, &ptr, tmp);
		ft_strdel(&tmp);
	}
	if (closedir(dir_id))
		ft_error("closedir in autocomp", "failed closing dir", curr_path);
	return (first);
}

char		**get_valid_content_from_path(t_env *e, char *curr_path, char *arg)
{
	char			**content;
	char			**tmp;
	char			*elem_match;
	t_list			*sorted_files;
	t_list			*ptr;

	content = NULL;
	sorted_files = dir_to_list(e, curr_path);
	merge_sort(&sorted_files);
	ptr = sorted_files;
	while (ptr)
	{
		if (ft_start_with_bis(ptr->content, arg))
		{
			elem_match = ft_strsub(ptr->content, ft_strlen(arg)
				, ft_strlen(ptr->content) - ft_strlen(arg));
			tmp = content;
			content = ft_tabcat(content, elem_match);
			ft_free_tab(tmp);
			ft_strdel(&elem_match);
		}
		ptr = ptr->next;
	}
	ft_lstdel(&sorted_files, ft_bzero);
	return (content);
}
