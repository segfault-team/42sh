/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_strsplit_quote_bs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:50:50 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:51:33 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Description for strsplit_quote:
**		behave like strsplit(), but keeps hold string into quotes.
*/

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
			if (!qt && (*s != c && (*(s + 1) == c || *(s + 1) == '\0')))
				++nw;
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
			if (bs)
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
			if (bs)
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

t_magic			*struct_strsplit_quote_bs(char const *s, char c)
{
	size_t		k;
	size_t		len;
	t_magic		*magic;

	if (s != NULL)
	{
		len = ft_count_words(s, c, '\0');
		if (!(magic = (t_magic *)malloc(sizeof(t_magic) * (len + 1))))
			return (NULL);
		struct_init(len, magic);
		k = 0;
		while (k < len && *s != '\0')
		{
			while (*s == c)
				++s;
			magic[k].cmd = ft_strcpy_chr(s, c, '\0');
			if (magic[k].cmd == NULL)
				return (NULL);
			s += ft_skip(s, c, '\0');
			++k;
		}
		return (magic);
	}
	return (NULL);
}
