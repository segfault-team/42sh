#include "shell.h"
#include <stdlib.h>

static size_t		ft_nwords(char const *str, char div)
{
	int		i;
	size_t	nwds;

	i = 0;
	nwds = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (i > 0 && str[i] == div && str[i - 1] != div)
				++nwds;
			else if (i == 0 && str[i] != div)
				++nwds;
			++i;
		}
	}
	return (nwds);
}

static size_t		ft_wordlen(char const *str, char div)
{
	size_t	wlen;

	wlen = 0;
	while (str[wlen] != '\0' && str[wlen] != div)
		++wlen;
	return (wlen);
}

static void			struct_init(int len, t_magic *magic)
{
	int	i;

	i = -1;
	while (++i <= len)
	{
		magic[i].cmd = NULL;
		magic[i].type = NULL;
	}
}

t_magic				*struct_strsplit(char const *str, char div)
{
	t_magic	*magic;
	size_t	nwords;
	size_t	wlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nwords = ft_nwords(str, div);
	if (nwords <= 0 || (magic = (t_magic *)malloc(sizeof(t_magic) * nwords)) == NULL)
		return (NULL);
	struct_init(nwords, magic);
	while (i < (int)ft_strlen(str))
	{
		if ((wlen = ft_wordlen(&str[i], div)))
		{
			if ((magic[j].cmd = ft_strndup(&str[i], wlen)) == NULL)
				break ;
			i += wlen;
			++j;
			magic[j].cmd = NULL;
		}
		else
			++i;
	}
	return (magic);
}
