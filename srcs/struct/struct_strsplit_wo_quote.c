#include "shell.h"

/*
**	Description for strsplit_wo_quote:
**		behave like strsplit(), but keeps hold string into quotes.
**	Like strsplit_quote, but it avoids copying quotes
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
			if (quote == '\0' && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			{
				//if (!bs) // || s[i] == '\\')
				++nw;
			}
			if (!quote && bs && s[i] == c && (s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
		++i;
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
			//		if ((quote && s[i] != quote) ||
			//				(!quote && (s[i] != '\'' && s[i] != '\"')))
			++len;
			bs = 0;
		}
		++i;
	}
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
			if ((quote && (s[i] != quote || bs)) ||
					(!quote && ((s[i] != '\'' && s[i] != '\"'))))// || bs)))
			cpy[j++] = s[i];
			bs = 0;
		}
		++i;
	}
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
	char	**tabb;
	size_t	nw;
	size_t	i;

	tabb = NULL;
	if (s)
	{
		i = -1;
		nw = ft_count_words(s, c);
		if ((tabb = ft_tabnew(nw + 1)) == NULL)
			return (NULL);
		while (++i < nw)
		{
			if ((tabb[i] = ft_strcpy_chr(s, c)) == NULL)
				return (tabb);
			s += ft_skip(s, c);
		}
	}
	return (tabb);
}

static void 	struct_init(int len, t_magic *magic)
{
	int i;

	i = -1;
	while (++i <= len)
	{
		magic[i].cmd = NULL;
		magic[i].type = NULL;
	}
}

t_magic			*struct_strsplit_wo_quote_bs(char const *s, char c)
{
	size_t		k;
	size_t		len;
	t_magic		*magic;

	if (s != NULL)
	{
		len = ft_count_words(s, c);
		if (!(magic = (t_magic *)malloc(sizeof(t_magic) * (len + 1))))
			return (NULL);
		struct_init(len, magic);
		k = 0;
		while (k < len && *s != '\0')
		{
			magic[k].cmd = ft_strcpy_chr(s, c);
			if (magic[k].cmd == NULL)
				return (NULL);
			s += ft_skip(s, c);
			++k;
		}
		return (magic);
	}
	return (NULL);
}
