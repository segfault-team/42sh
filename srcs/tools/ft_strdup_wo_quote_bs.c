/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_wo_quote_bs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:09:52 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:09:52 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	ft_strlen_wo_quote_bs(char const *s, char quote)
{
	size_t	len;
	int		i;
	int		bs;

	len = 0;
	i = 0;
	bs = 0;
	while (s[i])
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

static char		*ft_strdup_wo_quote_bs_bis(char const *s, size_t len,
		char quote, int bs)
{
	char	*dup;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if ((dup = ft_strnew(len)) == NULL)
		return (NULL);
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				dup[j++] = '\\';
			if ((!quote && !ft_isquote(s[i])) || bs || (quote && s[i] != quote))
				dup[j++] = s[i];
			bs = 0;
		}
	}
	return (dup);
}

char			*ft_strdup_wo_quote_bs(char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen_wo_quote_bs(s, '\0');
	dup = ft_strdup_wo_quote_bs_bis(s, len, '\0', 0);
	return (dup);
}
