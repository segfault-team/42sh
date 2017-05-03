/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:10:02 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/03 15:35:30 by vlistrat         ###   ########.fr       */
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
	return (quote);
}

char	*is_bad_line(char *line, char quote)
{
	int		i;
	char	*new;

	new = NULL;
	if (!line)
		return (NULL);
	if (line[0] && !quote && (line[0] == '|' || line[0] == '&'
				|| line[0] == ';'))
	{
		new = ft_strjoin(" ", line);
		strfree(&line);
	}
	else
		new = line;
	return (new);
}
