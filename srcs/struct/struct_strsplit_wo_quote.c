#include "shell.h"

/*
**	Description for strsplit_wo_quote:
**		behave like strsplit(), but keeps hold string into quotes.
**	Like strsplit_quote, but it avoids copying quotes
*/

static size_t	ft_count_words(char const *s, char c, char quote)
{
	size_t	nw;
	int		i;
	int		bs;

	i = -1;
	nw = 0;
	bs = 0;
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (!quote && !bs && s[i] != c &&
					(s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			if (!quote && bs && s[i] == c &&
					(s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
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
			if (bs && ((quote == '\'' && s[i] == '\\') ||
					(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				++len;
			++len;
			bs = 0;
		}
		++i;
	}
	return (len);
}

static char		*ft_strcpy_chr(char const *s, char c, char quote, int bs)
{
	char	*cpy;
	int		i;
	int		j;

	if ((cpy = ft_strnew(ft_strlen_chr(s, c))) == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i] && (s[i] != c || quote || (bs && s[i] == c)))
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			cpy[j++] = s[i];
			bs = 0;
		}
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
			quote = ft_check_quote_bs(s[i], quote, bs);
			bs = 0;
		}
		++i;
	}
	while (s[i] == c)
		++i;
	return (i);
}

t_magic			*struct_strsplit_wo_quote_bs(char const *s, char c)
{
	size_t		k;
	size_t		len;
	t_magic		*magic;

	if (s != NULL)
	{
		while (*s == c)
			++s;
		len = ft_count_words(s, c, '\0');
		if (!(magic = (t_magic *)malloc(sizeof(t_magic) * (len + 1))))
			return (NULL);
		struct_init(len, magic);
		k = -1;
		while (++k < len && *s != '\0')
		{
			if ((magic[k].cmd = ft_strcpy_chr(s, c, '\0', 0)) == NULL)
				return (magic);
			s += ft_skip(s, c);
		}
		return (magic);
	}
	return (NULL);
}
