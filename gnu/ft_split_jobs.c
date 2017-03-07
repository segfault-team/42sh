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
				//if (!bs)// || s[i] == '\\')
				++nw;
			}
			if (!quote && bs && s[i] == c && (s[i + 1] == c || s[i + 1] == '\0'))
				++nw;
			bs = 0;
		}
		++i;
	}
	//ft_printf("nw: %d\n", nw);
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
		{
			bs = 1;
			if (s[i + 1] != c)
				cpy[j++] = s[i];
		}
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			if (bs && ((quote == '\'' && s[i] == '\\') ||
						(quote == '\"' && s[i] != '\\' && s[i] != '\"')))
				cpy[j++] = '\\';
			//		if ((quote && s[i] != quote) ||
			//				(!quote && (s[i] != '\'' && s[i] != '\"')))
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

t_job			*ft_split_jobs(char const *s, char c)
{
	t_job	*jb;
	t_job	*ptr;
	size_t	len;
	size_t	i;

	jb = NULL;
	if (s)
	{
		i = 0;
		len = ft_strlen(s);
		if ((jb = ft_new_job()) == NULL)
			return (NULL);
		ptr = jb;
		while (i < len)
		{
			if ((ptr->command = ft_strcpy_chr(&s[i], c)) == NULL)
				return (jb);
			i += ft_skip(&s[i], c);
			if (i < len)
			{
				ptr->next = ft_new_job();
				ptr = ptr->next;
			}
		}
	}
	return (jb);
}
