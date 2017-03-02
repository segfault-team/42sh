/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:04:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/02 17:45:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	nw;
	int		i;
	int		bs;
	char	quote;

	i = 0;
	nw = 0;
	bs = 0;
	quote = '\0';
	while (s[i] && s[i] == c)
		++i;
	while (s[i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (quote == '\0' && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			{
				if (!bs || s[i] == '\\')
					++nw;
			}
			else if (!quote && bs && s[i] == c && (s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
		++i;
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
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
		{
			bs = 1;
			if (s[i + 1] != c)
				++len;
		}
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
			//		if ((quote && s[i] != quote) ||
			//				(!quote && (s[i] != '\'' && s[i] != '\"')))
			++len;
			bs = 0;
		}
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
	int		bs;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	bs = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
		{
			bs = 1;
			if (s[i + 1] != c)
				cpy[j++] = s[i];
		}
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			//		if ((quote && s[i] != quote) ||
			//				(!quote && (s[i] != '\'' && s[i] != '\"')))
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
