/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_ampersand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:49:30 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:49:30 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_not_src_fd(t_env *e, int *i)
{
	if (!is_number(e->line[*i - 2]) && e->line[*i - 2] != ' ')
	{
		insert_char(e, ' ', (*i)++ - 1);
		return (0);
	}
	else if (is_number(e->line[*i - 2]))
		return (0);
	return (1);
}

static void	manage_src_fd(t_env *e, int *i)
{
	int	k;

	k = *i - 1;
	while (e->line[--k] && e->line[k] == ' ')
		;
	while (k && is_number(e->line[k]))
		--k;
	if (k && e->line[k] && e->line[k] == ' ')
		delete_char(e, --(*i) - 1);
}

static void	manage_dst_fd(t_env *e, int *i)
{
	int	k;

	k = *i;
	while (e->line[++k] && e->line[k] == ' ')
		;
	if (e->line[k + 1] && is_number(e->line[k + 1]))
		delete_char(e, *i + 1);
}

static void	manage_parsing_aggregator(t_env *e, int *i)
{
	if (*i && is_not_src_fd(e, i))
		manage_src_fd(e, i);
	if (*i + 1 < (int)ft_strlen(e->line) && e->line[*i + 1] == ' ')
		manage_dst_fd(e, i);
}

void		check_parsing_ampersand(t_env *e, int *i)
{
	if (*i + 1 < (int)ft_strlen(e->line) && *i
		&& (e->line[*i - 1] == '>' || e->line[*i - 1] == '<'))
		manage_parsing_aggregator(e, i);
	else if (*i > 1 && e->line[*i - 1] && e->line[*i - 2]
		&& e->line[*i - 1] == '&' && e->line[*i - 2] == '&')
		insert_char(e, ' ', (*i)++);
	else if (*i && *i + 1 < (int)ft_strlen(e->line) && e->line[*i + 1]
			&& e->line[*i - 1] == '&' && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}
