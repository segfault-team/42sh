/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:49:12 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:49:12 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_only_numbers_before(char *s, int i)
{
	while (--i && s[i] && s[i] != ' ')
		if (!is_number(s[i]))
			return (0);
	return (1);
}

static int	start_by_nb(char *s, int i, int c)
{
	while (s[--i] && s[i] == c)
		;
	if (is_number(s[i]))
		return (1);
	return (0);
}

static int	check_parsing_double_bis(t_env *e, int *i, char c)
{
	if (*i > 1 && e->line[*i - 1] && e->line[*i - 2]
		&& e->line[*i - 1] == c && e->line[*i - 2] == c)
		insert_char(e, ' ', (*i)++);
	if (*i + 1 <= (int)ft_strlen(e->line) - 1 && e->line[*i + 1] &&
		e->line[*i + 1] != c && e->line[*i + 1] != ' '
		&& !start_by_nb(e->line, *i, e->line[*i]))
		insert_char(e, ' ', ++(*i));
	return (0);
}

int			check_parsing_double(t_env *e, int *i, char c)
{
	if (e->line[*i + 2] && e->line[*i + 1]
		&& e->line[*i + 1] == '>' && e->line[*i + 2] == '&')
	{
		ft_putchar('\n');
		return (ft_error(NULL, "Ambiguous redirection", NULL));
	}
	if (*i && e->line[*i - 1] && is_number(e->line[*i - 1])
		&& is_only_numbers_before(e->line, *i)
		&& e->line[*i + 1] && e->line[*i + 1] != '&')
	{
		if (e->line[*i + 1] == ' ')
			e->line[++*i] = '&';
		else if (e->line[*i + 1] != e->line[*i])
			insert_char(e, '&', ++(*i));
		return (0);
	}
	else if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	else if (is_special_aggre_in_line(e, *i)
			&& e->line[*i + 1] && e->line[*i + 1] == ' ')
		delete_char(e, *i + 1);
	return (check_parsing_double_bis(e, i, c));
}

void		check_parsing_simple(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i && e->line[*i + 1] && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}
