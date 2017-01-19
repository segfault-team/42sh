/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:15:17 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/05 17:25:31 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Description:
**		behave like ft_strsplit(), but keeps hold string into quotes.
**		returns a char **tab.
*/

static int		ft_count_words(char const *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = '\0';
	while (s[i] != '\0')
	{
		if (quote != '\0' && (s[i] == quote))
		{
			quote = '\0';
			++count;
		}
		else if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		if (quote == '\0' && ((i > 0 && s[i] != c && s[i - 1] == c) || \
					(i == 0 && s[i] != c)))
			++count;
		++i;
	}
	return (count);
}

static int		ft_strlen_ch(char const *s, char c, int i)
{
	int		len;
	char	quote;

	len = 1;
	quote = '\0';
	while (s[i] != c && s[i] != '\0')
	{
		if (quote != '\0' && s[i] == quote)
			quote = '\0';
		else if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] != quote)
			++len;
		++i;
	}
	return (len);
}

static char		*ft_strcpy_ch(char const *s, char c, int i)
{
	int		k;
	char	quote;
	char	*str;

	k = 0;
	quote = '\0';
	str = (char *)malloc(sizeof(*str) * (ft_strlen_ch(s, c, i) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
	{
		if (quote != '\0' && s[i] == quote)
			quote = '\0';
		else if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] != quote)
		{
			str[k] = s[i];
			++k;
		}
		++i;
	}
	str[k] = '\0';
	return (str);
}

int				ft_skiplen(char const *s, char c, int i)
{
	int		k;
	char	quote;

	k = 0;
	quote = '\0';
	while (s[i] != c && s[i] != '\0')
	{
		if (quote != '\0' && s[i] == quote)
			quote = '\0';
		else if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		++i;
		++k;
	}
	return (k);
}

char			**ft_strsplit_quote(char const *s, char c)
{
	int		i;
	int		k;
	char	**tab;

	if (s != NULL)
	{
		if (!(tab = (char **)malloc(sizeof(tab) * (ft_count_words(s, c) + 1))))
			return (NULL);
		i = 0;
		k = 0;
		while (k < ft_count_words(s, c) && s[i] != '\0')
		{
			while (s[i] == c)
				++i;
			tab[k] = ft_strcpy_ch(s, c, i);
			if (tab[k] == NULL)
				return (NULL);
			i += ft_skiplen(s, c, i);
			++k;
		}
		tab[k] = NULL;
		return (tab);
	}
	return (NULL);
}
