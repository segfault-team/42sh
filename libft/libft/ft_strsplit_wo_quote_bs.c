/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_wo_quote_bs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:51:29 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/04 10:31:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c, char quote)
{
	size_t	nw;
	int		i;
	int		bs;

	i = -1;
	nw = 0;
	bs = 0;
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (!quote && !bs && s[i] != c &&
					(s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			if (!quote && bs && s[i] == c &&
					(s[i + 1] == c || s[i + 1] == '\0'))
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
	i = 0;
	bs = 0;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
					(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
			if ((!quote && !ft_isquote(s[i])) || bs || (quote && s[i] != quote))
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

	if ((cpy = ft_strnew(ft_strlen_chr(s, c, '\0'))) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			if ((!quote && !ft_isquote(s[i])) || bs || (quote && s[i] != quote))
				cpy[j++] = s[i];
			bs = 0;
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

char			**ft_strsplit_wo_quote_bs(char const *s, char c)
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
