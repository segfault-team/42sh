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
