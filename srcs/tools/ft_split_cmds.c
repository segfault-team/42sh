/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:09:50 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:09:50 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Description:
**		this function split the line by the char ';',
**		it keeps hold '\' '\\' '\;' and things in quotes.
**		How it works? .. again, it's black magic.
*/

static size_t	ft_count_words(char const *s, char c, char quote, int bs)
{
	size_t	nw;
	int		i;

	i = 0;
	nw = 0;
	while (s[i] && s[i] == c)
		++i;
	while (s[i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (!quote && (s[i] != c &&
						(s[i + 1] == c || s[i + 1] == '\0')))
				++nw;
			if (!quote && bs && s[i] == c &&
					(s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
		++i;
	}
	return (nw);
}

static size_t	ft_strlen_chr(char const *s, char c, char quote, int bs)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'' && (bs = 1))
			len += (s[i + 1] != c) ? 1 : 0;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
			++len;
			bs = 0;
		}
		++i;
	}
	return (len);
}

static char		*ft_strcpy_chr(char const *s, char c, char quote, int bs)
{
	char	*cpy;
	int		i;
	int		j;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c, '\0', 0))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'' && (bs = 1))
			(s[i + 1] != c) ? cpy[j++] = s[i] : 0;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			cpy[j++] = s[i];
			bs = 0;
		}
		++i;
	}
	return (cpy);
}

static int		ft_skip(char const *s, char c)
{
	int		i;
	int		bs;
	char	quote;

	i = 0;
	bs = 0;
	quote = '\0';
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			bs = 0;
		}
		++i;
	}
	while (s[i] == c)
		++i;
	return (i);
}

char			**ft_split_cmds(char const *s, char c)
{
	char	**tab;
	size_t	nw;
	size_t	i;

	tab = NULL;
	if (s)
	{
		i = -1;
		nw = ft_count_words(s, c, '\0', 0);
		if ((tab = ft_tabnew(nw + 1)) == NULL)
			return (NULL);
		while (++i < nw)
		{
			if ((tab[i] = ft_strcpy_chr(s, c, '\0', 0)) == NULL)
				i--;
			s += ft_skip(s, c);
		}
	}
	return (tab);
}
