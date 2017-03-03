#include "shell.h"

/*
**	Description for strsplit_quote:
**		behave like strsplit(), but keeps hold string into quotes.
*/

static size_t	ft_count_words(char const *s, char c)
{
	size_t	nw;
	int		i;
	char	quote;

	i = 0;
	nw = 0;
	quote = '\0';
	while (s[i] && s[i] == c)
		++i;
	while (s[i])
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))	
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		if (quote == '\0' && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			++nw;
		++i;
	}
	return (nw);
}

static size_t	ft_strlen_chr(char const *s, char c)
{
	size_t	len;
	int		i;
	char	quote;

	len = 0;
	i = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
//		if ((quote && s[i] != quote) ||
//				(!quote && (s[i] != '\'' && s[i] != '\"')))
			++len;
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

	if ((cpy = ft_strnew(ft_strlen_chr(s, c))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
//		if ((quote && s[i] != quote) ||
//				(!quote && (s[i] != '\'' && s[i] != '\"')))
			cpy[j++] = s[i];
		++i;
	}
	return (cpy);
}

static int		ft_skip(char const *s, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (s[i] == c)
		++i;
	while (s[i] && (s[i] != c || quote))
	{
		if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (s[i] == quote)
			quote = '\0';
		++i;
	}
	return (i);
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

t_magic			*struct_strsplit_quote(char const *s, char c)
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
		while (k < len /*ft_count_words(s, c)*/ && *s != '\0')
		{
			while (*s == c)
				++s;
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
