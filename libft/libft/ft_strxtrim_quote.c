/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strxtrim_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:32:04 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 17:33:21 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	DESCRIPTION:
**		Trim str from chars x (avoiding quotes) and return the new
**		NULL terminated trimmed string.
*/

static char		ft_quote(char quote, char c)
{
	if (quote == '\0' && (c == '\'' || c == '\"'))
		quote = c;
	else if (quote != '\0' && quote == c)
		quote = '\0';
	return (quote);
}

static size_t	ft_trim_len_quote(const char *str, char x)
{
	int		i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	quote = '\0';
	while (str[i])
	{
		quote = ft_quote(quote, str[i]);
		if (quote != '\0' || str[i] != x)
			++len;
		++i;
	}
	return (len);
}

char			*ft_strxtrim_quote_ret(char const *str, char x, int len)
{
	char	*trim;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	trim = NULL;
	quote = '\0';
	if ((trim = ft_strnew(len)) == NULL)
		return (NULL);
	while (str[i])
	{
		quote = ft_quote(quote, str[i]);
		if (quote != '\0' || str[i] != x)
			trim[j++] = str[i];
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
		return (ft_strxtrim_quote_ret(str, x, len));
	}
	return (NULL);
}
