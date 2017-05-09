/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:10:02 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:10:02 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_path_from_arg(t_env *e, char *arg)
{
	char	*path;
	int		i;
	int		x;
	char	*tmp;

	i = ft_strlen(arg);
	while (i > 0 && arg[i - 1] != '/')
		--i;
	if (!arg || !i || (i > 0 && arg[i - 1] == ' '))
		return ((path = getcwd(NULL, 0)));
	path = ft_strnew(i);
	ft_strncpy(path, arg, i);
	x = 0;
	while (path[x])
	{
		if (path[x] == '\\')
			ft_strncpy(&path[x], &path[x + 1], i - x - 1);
		x++;
	}
	tmp = path;
	substitution(e, &path, '\0', 0);
	return (path);
}

char		*isolate_arg_to_complete(char *arg)
{
	int		i;
	int		j;
	char	*ret;

	i = ft_strlen(arg);
	if (!arg || !i)
		return (arg);
	j = 0;
	while (i > 0 && arg[i - 1] != '/')
		--i;
	if (!(ret = ft_strnew(ft_strlen(arg) - i)))
		return (NULL);
	while (arg[i])
		ret[j++] = arg[i++];
	return (ret);
}

static void	change_type(int *type, char *str, int x)
{
	if (!x)
		*type = 1;
	else
	{
		*type = 2;
		while (x)
		{
			if (str[x] == ';'
				|| str[x] == '&'
				|| str[x] == '|')
				*type = 1;
			x--;
		}
	}
}

char		*add_backquote(t_env *e, char *str, int i, int *type)
{
	int		x;
	int		quote;
	char	*ret;

	x = i;
	quote = cur_inquote(e->line, NB_MOVE - 1);
	if (quote)
	{
		quote = quote == 1 ? '\'' : '\"';
		while (x > 0 && str[x] != quote)
			x--;
	}
	else
	{
		while (x > 0 && ((str[x] != ' ' && str[x] != '	'
			&& str[x] != '\'' && str[x] != '\"') || ft_is_escaped(str, x)))
			x--;
	}
	if (str[x] == quote || str[x] == ' ')
		x++;
	ret = ft_strsub(str, x, i - x + 1);
	change_type(type, str, x);
	return (ret);
}

int			auto_completion(t_env *e)
{
	char	*arg_comp;
	int		type;

	type = 0;
	arg_comp = NULL;
	if (!e->line || !NB_MOVE)
		type = 1;
	if (e->selected >= -1 && e->files)
	{
		e->selected = e->files[e->selected + 1] ? e->selected + 1 : 0;
		print_auto_completion(e, NULL, NULL, NULL);
	}
	else
	{
		if (!type)
			arg_comp = add_backquote(e, e->line, TCAPS.nb_move - 1, &type);
		complete_arg(e, arg_comp, type);
		ft_strdel(&arg_comp);
	}
	return (1);
}
