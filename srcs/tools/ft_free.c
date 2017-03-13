/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 18:29:43 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/13 09:51:13 by kboddez          ###   ########.fr       */
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

void		ft_env_free(t_env *e)
{
	if (e->line)
		strfree(&e->line);
	if (e->home)
		strfree(&e->home);
	if (e->history)
		ft_free_tab(e->history);
	if (e->prompt)
		strfree(&e->prompt);
	if (e->env)
		ft_free_tab(e->env);
	if (e->magic)
		magic_free(e);
	if (close(HISTORY_FD) == -1)
		ft_error("close", "Could not close file", HIST_FILE);
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
