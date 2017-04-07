/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:52 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_redir_sign(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	struct_init(int len, t_magic *magic)
{
	int i;

	i = -1;
	while (++i <= len)
	{
		magic[i].cmd = NULL;
		magic[i].type = NULL;
	}
}

int		is_magic(t_env *e, int i)
{
	if (e->magic[i].cmd)
		return (1);
	return (0);
}

int		struct_len(t_magic **magic)
{
	int	len;

	len = 0;
	if (*magic)
		while ((*magic)[len].cmd)
			++len;
	return (len);
}

void	magic_free(t_env *e)
{
	int	i;

	i = -1;
	if (e->magic)
	{
		while (e->magic[++i].cmd)
		{
			if (e->magic[i].cmd)
			{
				free(e->magic[i].cmd);
				e->magic[i].cmd = NULL;
			}
			if (e->magic[i].type)
			{
				free(e->magic[i].type);
				e->magic[i].type = NULL;
			}
		}
		free(e->magic);
		e->magic = NULL;
	}
}
