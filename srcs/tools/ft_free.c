/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:29:43 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/09 18:56:49 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_free_line(t_env *e)
{
	if (e->line)
	{
		free(e->line);
		e->line = NULL;
	}
}

void		ft_env_free(t_env *e)
{
	if (e->line)
		free(e->line);
	if (e->home)
		free(e->home);
	if (TCAPS.term_name)
		free(TCAPS.term_name);
	// DOUBLE FREE ??
	//	if (e->history)
	//		ft_free_tab(e->history);
	if (e->prompt)
		free(e->prompt);
	if (e->env)
		ft_free_tab(e->env);
	if (e->magic)
		magic_free(e);
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
