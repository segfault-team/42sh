/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_content_from_path_fill.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 17:08:44 by aleghmar          #+#    #+#             */
/*   Updated: 2017/05/09 17:25:40 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_list	*dir_to_list(t_env *e, char *curr_path)
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

static void		binary_dir_to_list(t_list **first, t_list **ptr, char *path)
{
	DIR				*dir_id;
	struct dirent	*dir_entry;
	char			*tmp;

	dir_id = opendir(path);
	while (dir_id && (dir_entry = readdir(dir_id)) != NULL)
	{
		tmp = ft_strdup(dir_entry->d_name);
		ft_add_list(first, ptr, tmp);
		ft_strdel(&tmp);
	}
	if (dir_id && closedir(dir_id))
		ft_error("closedir in autocomp", "failed closing dir", path);
}

static t_list	*binary_to_list(t_env *e)
{
	t_list			*first;
	t_list			*ptr;
	int				x;
	char			**paths;

	x = 0;
	first = NULL;
	paths = ft_find_paths(e->env);
	while (paths && paths[x])
	{
		binary_dir_to_list(&first, &ptr, paths[x]);
		x++;
	}
	ft_free_tab(paths);
	return (first);
}

static t_list	*env_to_list(t_env *e)
{
	t_list			*first;
	t_list			*ptr;
	int				x;
	int				y;
	char			*tmp;

	first = NULL;
	x = 0;
	while (e->env[x])
	{
		y = 0;
		while (e->env[x] && e->env[x][y] && e->env[x][y] != '=')
			y++;
		tmp = ft_strnew(x + 3);
		tmp[0] = '$';
		ft_strncpy(&tmp[1], e->env[y], y);
		ft_add_list(&first, &ptr, tmp);
		ft_strdel(&tmp);
		x++;
	}
	return (first);
}

t_list			*pick_destination(t_env *e, char *curr_path, char *arg,
									int type)
{
	t_list *ret;

	ret = NULL;
	if (arg && *arg == '$')
		ret = env_to_list(e);
	else if (type == 2)
		ret = dir_to_list(e, curr_path);
	else
		ret = binary_to_list(e);
	return (ret);
}
