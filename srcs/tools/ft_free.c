/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:23 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	strfree(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_env_free(t_env *e)
{
	if (e->new_term)
		free(e->new_term);
	if (e->old_term)
		free(e->old_term);
	strfree(&e->line);
	strfree(&e->home);
	strfree(&e->prompt);
	strfree(&HIST_FILE);
	strfree(&e->herestock);
	strfree(&e->last_ret);
	strfree(&e->susp);
	if (e->env)
		ft_free_tab(e->env);
	if (e->history)
		ft_free_tab(e->history);
	if (e->magic)
		magic_free(e);
	if (e->hdoc_words)
		ft_free_tab(e->hdoc_words);
	free(e);
}

void	ft_triple_free(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	if (e->cat)
	{
		while (e->cat[++i])
		{
			j = -1;
			while (e->cat[i][++j])
			{
				free(e->cat[i][j]);
				e->cat[i][j] = NULL;
			}
			free(e->cat[i]);
			e->cat[i] = NULL;
		}
		free(e->cat);
		e->cat = NULL;
	}
}

char	**new_tabcat(char ***oldtab, char **str)
{
	char	**ret;

	ret = ft_tabcat(*oldtab, *str);
	ft_free_tab(*oldtab);
	strfree(str);
	return (ret);
}
