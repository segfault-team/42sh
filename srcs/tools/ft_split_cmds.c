/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:04:28 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/29 16:14:24 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Description:
**		this function split the line by the char ';',
**		it keeps hold '\' '\\' '\;' and things in quotes.
**		How it works? .. again, it's black magic.
*/

static size_t	ft_count_words(char const *s, char c, char qt)
{
	size_t	nw;
	int		i;
	int		bs;

	i = -1;
	nw = 0;
	bs = 0;
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && qt != '\'')
			bs = 1;
		else
		{
			qt = ft_check_quote_bs(s[i], qt, bs);
			if (qt == '\0' && (s[i] != c &&
						(s[i + 1] == c || s[i + 1] == '\0')))
				++nw;
			if (!qt && bs && s[i] == c && (s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
	}
	return (nw);
}

static size_t	ft_strlen_chr(char const *s, char c, char quote)
{
	size_t	len;
	int		i;
	int		bs;

	len = 0;
	i = -1;
	bs = 0;
	while (s[++i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
		{
			bs = 1;
			len += (s[i + 1] != c) ? 1 : 0;
		}
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
			++len;
			bs = 0;
		}
	}
	return (len);
}

static char		*ft_strcpy_chr(char const *s, char c, char quote, int bs)
{
	char	*cpy;
	int		i;
	int		j;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c, '\0') + 1)) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'' && (bs = 1))
		{
			if (s[i + 1] != c)
				cpy[j++] = s[i];
		}
		else if (!(bs = 0))
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			cpy[j++] = s[i];
		}
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
	while (s[i] == c)
		++i;
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
		while (*s == c)
			++s;
		nw = ft_count_words(s, c, '\0');
		if ((tab = ft_tabnew(nw + 1)) == NULL)
			return (NULL);
		while (++i < nw)
		{
			if ((tab[i] = ft_strcpy_chr(s, c, '\0', 0)) == NULL)
				return (tab);
			s += ft_skip(s, c);
		}
	}
	return (tab);
}
