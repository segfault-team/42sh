/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:28:05 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/29 14:28:18 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_check_quote_bs(char c, char quote, int bs)
{
	if (quote == '\0' && !bs && (c == '\'' || c == '\"'))
		return (c);
	else if (c == quote && ((!bs && quote == '\"') || quote == '\''))
		return ('\0');
	return (quote);
}

char	ft_check_quote(char c, char quote)
{
	if (quote == '\0' && (c == '\'' || c == '\"'))
		return (c);
	else if (c == quote)
		return ('\0');
	return (quote);
}
