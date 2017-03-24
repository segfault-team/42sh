#include "shell.h"

static int	ft_start_with_bis(char *str, char *comp)
{
	int	i;

	i = -1;
	if (ft_strlen(str) < ft_strlen(comp))
		return (0);
	while (comp && comp[++i])
	{
		if (comp[i] && comp[i] != str[i])
			return (0);
	}
	if (str[0] == '.' && i <= 0)
		return (0);
	return (1);
}

int			ft_sort(void *one, void *two)
{
	const char *top;
	const char *kek;

	top = one;
	kek = two;
	if (ft_strcmp(top, kek) > 0)
		return (0);
	else
		return (1);
}

int			ft_lstswap(t_list *one, t_list *two)
{
	int		tmp_content_size;
	char	*tmp_content;

	tmp_content = one->content;
	one->content = two->content;
	two->content = tmp_content;
	tmp_content_size = one->content_size;
	one->content_size = two->content_size;
	two->content_size = tmp_content_size;
	return (1);
}

t_list		*ft_sort_list(t_list *lst, int (*cmp)(void *, void *))
{
	int		modif;
	void	*flst;

	if (!cmp || !lst)
		return (NULL);
	flst = lst;
	modif = 1;
	while (modif == 1)
	{
		modif = 0;
		lst = flst;
		while (lst && lst->next)
		{
			if (cmp(lst->content, lst->next->content) == 0)
				modif = ft_lstswap(lst, lst->next);
			lst = lst->next;
		}
	}
	return (flst);
}

void		ft_add_list(t_list **first, t_list **ptr, char *str)
{
	if (!*first)
	{
		*first = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = *first;
	}
	else
	{
		(*ptr)->next = ft_lstnew(str, ft_strlen(str) + 1);
		*ptr = (*ptr)->next;
	}
}

int			ft_countchar(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			++i;
		++str;
	}
	return (i);
}

char		*escape_spaces(char *str)
{
	char	*tmp;
	char	*ret;
	int		k;

	k = ft_countchar(str, ' ') + ft_countchar(str, '	');
	tmp = ft_strnew(strlen(str) + k);
	ret = tmp;
	while (*str)
	{
		if (*str == ' ' || *str == '	')
		{
			*tmp = '\\';
			tmp++;
		}
		*tmp = *str;
		++tmp;
		++str;
	}
	return (ret);
}

int			cur_inquote(t_env *e)
{
	int s_quote;
	int d_quote;
	int pos;

	s_quote = 0;
	d_quote = 0;
	pos = NB_MOVE - 1;
	while (e->line[pos] && pos)
	{
		if (e->line[pos] == '\'')
			s_quote++;
		else if (e->line[pos] == '\"')
			d_quote++;
		pos--;
	}
	if (d_quote % 2)
		return (1);
	if (s_quote % 2)
		return (1);
	return (0);
}

t_list		*dir_to_list(t_env *e, char *curr_path)
{
	DIR				*dir_id;
	struct dirent	*dir_entry;
	t_list			*first;
	t_list			*ptr;
	char			*tmp;

	first = NULL;
	if ((dir_id = opendir(curr_path)) == NULL)
		return (NULL);
	while ((dir_entry = readdir(dir_id)) != NULL)
	{
		if (!cur_inquote(e))
			tmp = escape_spaces(dir_entry->d_name);
		else
			tmp = ft_strdup(dir_entry->d_name);
		if (ft_strcmp(tmp, ".") && ft_strcmp(tmp, ".."))
			ft_add_list(&first, &ptr, tmp);
		ft_strdel(&tmp);
	}
	if (closedir(dir_id))
		ft_error("closedir", "failed closing dir", curr_path);
	return (first);
}

char		**get_valid_content_from_path(t_env *e, char *curr_path, char *arg)
{
	char			**content;
	char			**tmp;
	char			*elem_match;
	t_list			*sorted_files;
	t_list			*ptr;

	content = NULL;
	sorted_files = ft_sort_list(dir_to_list(e, curr_path), ft_sort);
	ptr = sorted_files;
	while (ptr)
	{
		if (ft_start_with_bis(ptr->content, arg))
		{
			elem_match = ft_strsub(ptr->content, ft_strlen(arg)
				, ft_strlen(ptr->content) - ft_strlen(arg));
			tmp = content;
			content = ft_tabcat(content, elem_match);
			ft_free_tab(tmp);
			ft_strdel(&elem_match);
		}
		ptr = ptr->next;
	}
	ft_lstdel(&sorted_files, ft_bzero);
	return (content);
}
