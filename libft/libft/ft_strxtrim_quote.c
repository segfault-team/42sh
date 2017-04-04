/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxtrim_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:32:04 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/04 15:18:23 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	DESCRIPTION:
**		Trim str from chars x (avoiding quotes) and return the new
**		NULL terminated trimmed string.
*/

static size_t	ft_trim_len_quote(const char *str, char x)
{
	int		i;
	int		bs;
	size_t	len;
	char	quote;

	i = 0;
	bs = 0;
	len = 0;
	quote = '\0';
	while (str[i])
	{
		if (!bs && str[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(str[i], quote, bs);
			if (quote || str[i] != x || bs)
				++len;
			bs = 0;
		}
		++i;
	}
	return (len);
}

static char		*ft_strxtrim_quote_ret(char const *str, char x,
		int len, char quote)
{
	char	*trim;
	int		bs;
	int		i;
	int		j;

	bs = 0;
	i = 0;
	j = 0;
	if ((trim = ft_strnew(len)) == NULL)
		return (NULL);
	while (str[i])
	{
		if (!bs && str[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(str[i], quote, bs);
			if (quote || str[i] != x || bs)
				trim[j++] = str[i];
			bs = 0;
		}
		++i;
	}
	trim[j] = '\0';
	return (trim);
}

char			*ft_strxtrim_quote(char const *str, char x)
{
	size_t	len;

	if (str)
	{
		len = ft_trim_len_quote(str, x);
		return (ft_strxtrim_quote_ret(str, x, len, '\0'));
	}
	return (NULL);
}
