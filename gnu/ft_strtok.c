#include "libft.h"
#include "jc.h"

/*
**
**	Description: (this is a simple state machine)
**		this function split the line by the char ';',
**		it keeps hold '\' '\\' '\;' and things in quotes.
**		How it works? .. again, it's black magic.
**
*/

static char		*ft_strchr_tok(char const *s, char c)
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
	return (&s[len]);
}

static int		ft_strcspn_tok(char const *s, char c)
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

char			*ft_strtok_inhib(char *s, const char c)
{
	static char		*lasts;

}
