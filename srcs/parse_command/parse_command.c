/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:49:44 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:50:15 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	manage_chev(t_env *e, int *i)
{
	if (*i && e->line[*i - 1] == '&')
	{
		ft_putchar('\n');
		return (ft_error(NULL, "Ambiguous redirection", NULL));
	}
	else if (*i + 1 < (int)ft_strlen(e->line))
	{
		if (e->line[*i + 1] && e->line[*i + 1] != '&')
			return (check_parsing_double(e, i, e->line[*i]));
		while (e->line[*i + 1] && e->line[*i + 2]
				&& (e->line[*i + 2] == ' ' || e->line[*i + 2] == '\t')
				&& e->line[*i + 2])
			delete_char(e, (*i + 2));
	}
	else if (*i > 1 && e->line[*i - 1] == e->line[*i]
			&& e->line[*i - 2] == e->line[*i])
		insert_char(e, ' ', *i);
	return (1);
}

int			parse_command(t_env *e)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	while (e->line[++i])
	{
		if (((e->line[i] == '\"') && ((i - 1 >= 0 &&
			e->line[i - 1] != '\\') || !i)) || e->line[i] == '\'')
		{
			if (!quote)
				quote = e->line[i];
			else if (quote == e->line[i])
				quote = '\0';
		}
		else if (!quote && (e->line[i] == '|' || e->line[i] == '<'))
			check_parsing_double(e, &i, e->line[i]);
		else if (!quote && e->line[i] == '&')
			check_parsing_ampersand(e, &i);
		else if (!quote && e->line[i] == ';')
			check_parsing_simple(e, &i, e->line[i]);
		else if (!quote && e->line[i] == '>' && manage_chev(e, &i) == -1)
			return (-1);
	}
	return (1);
}
