/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_wo_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:31:06 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/29 14:31:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	nw;
	int		i;
	char	quote;

	i = 0;
	nw = 0;
	quote = '\0';
	while (s[i] && s[i] == c)
		++i;
	while (s[i])
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		if (quote == '\0' && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			++nw;
		++i;
	}
	return (nw);
}

static size_t	ft_strlen_chr(char const *s, char c)
{
	size_t	len;
	int		i;
	char	quote;

	len = 0;
	i = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		if ((quote && s[i] != quote) ||
				(!quote && (s[i] != '\'' && s[i] != '\"')))
			++len;
		++i;
	}
	return (len);
}

static char		*ft_strcpy_chr(char const *s, char c)
{
	char	*cpy;
	int		i;
	int		j;
	char	quote;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		if ((quote && s[i] != quote) ||
				(!quote && (s[i] != '\'' && s[i] != '\"')))
			cpy[j++] = s[i];
		++i;
	}
	return (cpy);
}

static int		ft_skip(char const *s, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		++i;
	}
	return (i);
}

char			**ft_strsplit_wo_quote(char const *s, char c)
{
	char	**tab;
	size_t	nw;
	size_t	i;

	tab = NULL;
	if (s)
	{
		i = -1;
		nw = ft_count_words(s, c);
		if ((tab = ft_tabnew(nw + 1)) == NULL)
			return (NULL);
		while (++i < nw)
		{
			if ((tab[i] = ft_strcpy_chr(s, c)) == NULL)
				return (tab);
			s += ft_skip(s, c);
		}
	}
	return (tab);
}
