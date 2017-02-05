#include "shell.h"

static int		red_check_sign(char	c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}


static size_t ft_nwords(char const *str)
{
	int i;
	size_t nwds;

	i = 0;
	nwds = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (i > 0 && red_check_sign(str[i])  && !red_check_sign(str[i - 1]))
				++nwds;
			else if (i == 0 && !red_check_sign(str[i]))
				++nwds;
			++i;
		}
	}
	return (nwds);
}

static size_t ft_wordlen(char const *str, char div)
{
	size_t wlen;

	wlen = 0;
	while (str[wlen] != '\0' && !red_check_sign(str[wlen]))
		++wlen;
	return (wlen);
}

char	**red_split(char const *str)
{
	char	**tab;
	size_t nwords;
	size_t wlen;
	int i;
	int j;

	i = 0;
	j = 0;
	nwords = ft_nwords(str);
	if (nwords == 0 || (tab = ft_tabnew(nwords)) == NULL)
		return (NULL);
	while (i < (int)ft_strlen(str))
	{
		if ((wlen = ft_wordlen(&str[i])))
		{
			if ((tab[j] = ft_strndup(&str[i], wlen)) == NULL)
				break ;
			i += wlen;
			++j;
			tab[j] = NULL;
		}
		else
			++i;
	}
	return (tab);
}

char	**red_sign_split(char const *str)
{
	char	**tab;
	size_t nwords;
	size_t wlen;
	int i;
	int j;

	i = 0;
	j = 0;
	nbwords;
/*	nwords = ft_nwords(str);
	if (nwords == 0 || (tab = ft_tabnew(nwords)) == NULL)
		return (NULL);
	while (i < (int)ft_strlen(str))
	{
		if ((wlen = ft_wordlen(&str[i])))
		{
			if ((tab[j] = ft_strndup(&str[i], wlen)) == NULL)
				break ;
			i += wlen;
			++j;
			tab[j] = NULL;
		}
		else
			++i;
	}
	return (tab);*/
	while (str[++i])
	{
		if (red_check_sign(str[i]))
			++nbwords;
	}
	e->red_sign = ft_tabnew(nbwords);
	i = -1;
	while (str[++i])
	{
		if (red_check_sign(str[i]))
			e->red_sign[j][k] = str[i];
		if (red_check_sign(str[i + 1]))
		{
			++k;
			++i;
			e->red_sign[j][k] = str[i];
		}
	}
}


