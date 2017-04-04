#include "shell.h"

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

/*
**	bs == back slash
*/

int		check_quote(char *s)
{
	int		i;
	int		bs;
	char	quote;

	i = -1;
	bs = 0;
	quote = '\0';
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			bs = 0;
		}
	}
	if (quote != '\0')
		return (1);
	return (0);
}

int		is_bad_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != ' ')
		if (line[i] == '|' ||
			line[i] == '&' ||
			line[i] == ';')
			return (1);
	return (0);
}
