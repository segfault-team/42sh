/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:09:32 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:09:32 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	j = 0;
	if (!str)
		return (NULL);
	if (i > 0 && str[i])
		++i;
	while (str[++i])
		if (i && str[i - 1] == '<' && str[i] == '<')
			break ;
	if (!str[i])
	{
		i = -1;
		e->herestop = 0;
		return (NULL);
	}
	if (str[i + 1] && str[i + 1] != ' ')
		--i;
	j = find_word_end(i, str);
	return (ft_strsub(str, (i + 2), (j - (i + 2))));
}

static int	stop_heredocs(t_env *e)
{
	if (!e->herestop)
	{
		NB_READ = 0;
		NB_MOVE = 0;
		strfree(&e->line);
		strfree(&e->prompt);
		e->prompt = ft_strdup(BS_PROMPT);
		tcaps_ctrl_end(e);
		ft_putchar('\n');
		ft_prompt(e->prompt);
		return (0);
	}
	return (1);
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
	if (!stop_heredocs(e))
		return (0);
	return (1);
}
