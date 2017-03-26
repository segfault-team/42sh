#include "shell.h"

int store_heredoc(t_env *e)
{
	t_hdoc		*new;
	char		**tmp;
	static int	same_node = -1;
	static int	i = -1;

//	if (!ft_strcmp(e->line, e->hdoc_words[iz]))
//		return (--e->hdoc_nb);
	if (same_node != e->hdoc_nb)
	{
		new = (t_hdoc *)malloc(sizeof(*new));
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
		++i;
		same_node = e->hdoc_nb;
	}
	if (ft_strcmp(e->line, e->hdoc_words[i]))
	{
		tmp = e->hdoc->content;
		e->hdoc->content = ft_tabcat(e->hdoc->content, e->line);
		if (tmp)
			ft_free_tab(tmp);
		strfree(&e->line);
		ft_printf("\n%s", e->prompt);
	}
	else
	{
		strfree(&e->line);
		if (e->hdoc_nb - 1 == 0)
		{
			e->line = ft_strdup(e->herestock);
			strfree(&e->herestock);
			strfree(&e->prompt);
			e->prompt = ft_strdup(STD_PROMPT);
			same_node = -1;
			i = -1;
			e->hdoc = e->b_hdoc;
		}
		else
			ft_printf("\n%s", e->prompt);
		return (--e->hdoc_nb);
	}
	NB_READ = 0;
	NB_MOVE = 0;
	strfree(&e->line);
	return (e->hdoc_nb);
}
