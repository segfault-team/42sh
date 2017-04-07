/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:29 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:29 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

/*
**	bs == back slash
*/

char	check_quote(t_env *e, char *s)
{
	int		i;
	int		bs;
	char	quote;

	i = -1;
	bs = 0;
	quote = e->multi_quote;
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			bs = 0;
		}
	}
	if (quote != '\0')
		return (quote);
	return (quote);
}

int		is_bad_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != ' ')
		if (line[i] == '|' ||
			line[i] == '&' ||
			line[i] == ';')
			return (1);
	return (0);
}
