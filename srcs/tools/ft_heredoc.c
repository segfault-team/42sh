#include "shell.h"

static int	find_word_end(int i, char *str)
{
	int		j;

	j = i + 1;
	while (str[++j])
		if (str[j] == ' ')
			break ;
	return (j);
}

static char	*get_hdoc_word(t_env *e, char *str)
{
	static int	i = -1;
	int			j;
	int			last_in;

	j = 0;
	last_in = -1;
	if (!str)
		return (NULL);
	if (i > 0 && str[i] && str[i] == ';')
		++i;
	while (str[++i] && str[i] != ';')
		if (i && str[i - 1] == '<' && str[i] == '<')
			last_in = i;
	if (!str[i])
	{
		i = -1;
		e->herestop = 0;
	}
	if (last_in == -1)
		return (NULL);
	else
		i = last_in;
	j = find_word_end(last_in, str);
	return (ft_strsub(str, (last_in + 2), (j - (last_in + 2))));
}

int			ft_heredoc(t_env *e)
{
	char	*hdoc_word;

	if (!(hdoc_word = get_hdoc_word(e, e->line)))
		return (1);
	e->hdoc_words = new_tabcat(&e->hdoc_words, &hdoc_word);
	e->herestock = ft_strdup(e->line);
	e->herestop = 1;
	++e->hdoc_nb;
	while (e->herestop)
		if ((hdoc_word = get_hdoc_word(e, e->herestock)))
		{
			e->hdoc_words = new_tabcat(&e->hdoc_words, &hdoc_word);
			++e->hdoc_nb;
		}
	if (!e->herestop)
	{
		NB_READ = 0;
		NB_MOVE = 0;
		strfree(&e->line);
		strfree(&e->prompt);
		e->prompt = ft_strdup(BS_PROMPT);
		ft_printf("\n%s", e->prompt);
		return (0);
	}
	return (1);
}
