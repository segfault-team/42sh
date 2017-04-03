/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_quote_bs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:53:18 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/03 13:45:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c, char qt)
{
	size_t	nw;
	int		bs;

	nw = 0;
	bs = 0;
	while (*s)
	{
		if (!bs && *s == '\\' && qt != '\'')
			bs = 1;
		else
		{
			qt = ft_check_quote_bs(*s, qt, bs);
			if (qt == '\0' && (*s != c && (*(s + 1) == c || *(s + 1) == '\0')))
			{
				if (!bs || *s == '\\')
					++nw;
			}
			else if (!qt && bs && *s == c &&
					(*(s + 1) == c || *(s + 1) == '\0'))
				++nw;
			bs = 0;
		}
		++s;
	}
	return (nw);
}

static size_t	ft_strlen_chr(char const *s, char c)
{
	size_t	len;
	int		i;
	int		bs;
	char	quote;

	len = 0;
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
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"')))
				++len;
			++len;
			bs = 0;
		}
		++i;
	}
	return (len);
}

static char		*ft_strcpy_chr(char const *s, char c, char quote)
{
	char	*cpy;
	int		i;
	int		j;
	int		bs;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c))) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	bs = 0;
	while (s[++i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"')))
				cpy[j++] = '\\';
			cpy[j++] = s[i];
			bs = 0;
		}
	}
	return (cpy);
}

static int		ft_skip(char const *s, char c, char quote)
{
	int		i;
	int		bs;

	i = 0;
	bs = 0;
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			bs = 0;
		}
		++i;
	}
	while (s[i] == c)
		++i;
	return (i);
}

char			**ft_strsplit_quote_bs(char const *s, char c)
{
	char	**tab;
	size_t	nw;
	size_t	i;

	tab = NULL;
	if (s)
	{
		i = -1;
		nw = ft_count_words(s, c, '\0');
		if ((tab = ft_tabnew(nw + 1)) == NULL)
			return (NULL);
		while (++i < nw)
		{
			if ((tab[i] = ft_strcpy_chr(s, c, '\0')) == NULL)
				return (tab);
			s += ft_skip(s, c, '\0');
		}
	}
	return (tab);
}
