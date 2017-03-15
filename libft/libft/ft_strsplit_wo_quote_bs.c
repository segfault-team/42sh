/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_wo_quote_bs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:04:39 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/03 19:35:56 by lfabbro          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

/*
**
**	Description:
**		don't try to understand. It's black magic.
**
*/

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
			if (!quote && !bs && s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			{
				//if (!bs || s[i] == '\\')
					++nw;
			}
			if (!quote && bs && s[i] == c && (s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
		++i;
	}
	//ft_printf("nw: %d\n", nw);
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
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (bs && ((quote == '\'' && s[i] == '\\') ||
					(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
		//	if ((quote && (s[i] != quote || bs)) ||
		//		(!quote && ((s[i] == '\'' || s[i] == '\"') || bs)))
			++len;
			bs = 0;
		}
		++i;
	}
	//ft_printf("len: %d\n", len);
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
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
	//		if ((quote && (s[i] != quote || bs)) ||
	//			(!quote && ((s[i] == '\'' || s[i] == '\"') || bs)))
			cpy[j++] = s[i];
			bs = 0;
		}
		++i;
	}
	if (bs)
		cpy[j - 1] = '\0';
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

char			**ft_strsplit_wo_quote_bs(char const *s, char c)
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
