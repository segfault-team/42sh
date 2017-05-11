/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:26 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/11 14:02:27 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static unsigned int	get_hash_value(char *key)
{
	unsigned int	hash;
	int				i;

	hash = 0;
	i = -1;
	while (key[++i])
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash);
}

static char			*path_join(char *s1, char *s2)
{
	int		i;
	char	*cpy;
	size_t	len;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
		return ((s2 ? s2 : s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	cpy = ft_strnew(len + 1);
	while (*s1)
	{
		cpy[i] = *s1++;
		i++;
	}
	if (cpy[i - 1] != '/')
		cpy[i++] = '/';
	while (*s2)
	{
		cpy[i] = *s2++;
		i++;
	}
	return (cpy);
}

void				hash_gen(t_env *e, char **paths)
{
	unsigned int	hash;
	t_hash			*list;
	t_hash			*prev;
	int				i;

	list = NULL;
	prev = NULL;
	i = -1;
	while (paths[++i])
		if ((DIRP = opendir(paths[i])))
			while ((DP = readdir(DIRP)))
			{
				hash = get_hash_value(DP->d_name);
				list = (t_hash*)malloc(sizeof(t_hash));
				if (prev)
					prev->next = list;
				else
					e->hash = list;
				list->hash = hash;
				list->name = path_join(paths[i], DP->d_name);
				list->next = NULL;
				prev = list;
				list = list->next;
			}
	merge_sort_hash(&e->hash);
}
