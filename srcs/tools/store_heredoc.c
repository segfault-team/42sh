/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:10:06 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:10:06 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	put_new_node(t_env *e, int *same_node)
{
	t_list	*new;

	if (*same_node != e->hdoc_nb)
	{
		if (!(new = (t_list *)malloc(sizeof(t_list))))
			return (-1);
		new->content = NULL;
		new->next = NULL;
		if (!e->b_hdoc)
		{
			e->hdoc = new;
			++e->hdoc_index;
			e->b_hdoc = e->hdoc;
		}
		else
		{
			e->hdoc->next = new;
			e->hdoc = e->hdoc->next;
		}
		*same_node = e->hdoc_nb;
	}
	return (1);
}

static int	replace_line(t_env *e, int *same_node)
{
	strfree(&e->line);
	if (!e->hdoc->content)
		e->hdoc->content = ft_tabcat(e->hdoc->content, "");
	if (e->hdoc_nb - 1 == 0)
	{
		e->line = (e->herestock) ? ft_strdup(e->herestock) : e->line;
		strfree(&e->herestock);
		strfree(&e->prompt);
		e->prompt = ft_create_prompt(e, STD_PROMPT);
		*same_node = -1;
		e->hdoc_index = -1;
		e->hdoc = e->b_hdoc;
		if (e->hdoc_words)
			ft_free_tab(e->hdoc_words);
		e->hdoc_words = NULL;
	}
	else
	{
		tcaps_ctrl_end(e);
		ft_putchar('\n');
		ft_prompt(e->prompt);
		NB_READ = 0;
		++e->hdoc_index;
	}
	return (--e->hdoc_nb);
}

int			store_heredoc(t_env *e)
{
	char		**tmp;
	static int	same_node = -1;

	if ((put_new_node(e, &same_node)) < 0)
		return (-1);
	if (e->hdoc_index >= 0 && ft_strcmp(e->line, e->hdoc_words[e->hdoc_index]))
	{
		tmp = e->hdoc->content;
		e->line = (!e->line) ? ft_strdup("") : e->line;
		e->hdoc->content = ft_tabcat(e->hdoc->content, e->line);
		e->hdoc->content_size = sizeof(e->hdoc->content);
		if (tmp)
			ft_free_tab(tmp);
		strfree(&e->line);
		tcaps_ctrl_end(e);
		ft_putchar('\n');
		ft_prompt(e->prompt);
	}
	else
		return (replace_line(e, &same_node));
	NB_READ = 0;
	NB_MOVE = 0;
	strfree(&e->line);
	return (e->hdoc_nb);
}
