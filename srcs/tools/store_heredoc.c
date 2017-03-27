#include "shell.h"

static int	put_new_node(t_env *e, int *same_node)
{
	int		ret;
	t_list	*new;

	ret = 0;
	if (*same_node != e->hdoc_nb)
	{
		new = (t_list *)malloc(sizeof(t_list));
		new->content = NULL;
		new->next = NULL;
		if (!e->b_hdoc)
		{
			e->hdoc = new;
			e->b_hdoc = e->hdoc;
		}
		else
		{
			e->hdoc->next = new;
			e->hdoc = e->hdoc->next;
		}
		ret = 1;
		*same_node = e->hdoc_nb;
	}
	return (ret);
}

static int	replace_line(t_env *e, int *same_node, int *i)
{
	strfree(&e->line);
	if (e->hdoc_nb - 1 == 0)
	{
		e->line = ft_strdup(e->herestock);
		strfree(&e->herestock);
		strfree(&e->prompt);
		e->prompt = ft_strdup(STD_PROMPT);
		*same_node = -1;
		*i = -1;
		e->hdoc = e->b_hdoc;
	}
	else
		ft_printf("\n%s", e->prompt);
	return (--e->hdoc_nb);
}

int			store_heredoc(t_env *e)
{
	char		**tmp;
	static int	same_node = -1;
	static int	i = -1;

	i = put_new_node(e, &same_node);
	if (ft_strcmp(e->line, e->hdoc_words[i]))
	{
		tmp = e->hdoc->content;
		e->hdoc->content = ft_tabcat(e->hdoc->content, e->line);
		e->hdoc->content_size = sizeof(e->hdoc->content);
		if (tmp)
			ft_free_tab(tmp);
		strfree(&e->line);
		ft_printf("\n%s", e->prompt);
	}
	else
		return (replace_line(e, &same_node, &i));
	NB_READ = 0;
	NB_MOVE = 0;
	strfree(&e->line);
	return (e->hdoc_nb);
}
