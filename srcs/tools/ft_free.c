#include "shell.h"

void	strfree(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_split_delim(t_env *e)
{
	int	i;

	i = -1;
	while (SPLIT_DELIM[++i])
		strfree(&SPLIT_DELIM[i]);
}

void	ft_env_free(t_env *e)
{
	strfree(&e->line);
	strfree(&e->home);
	strfree(&e->prompt);
	strfree(&HIST_FILE);
	strfree(&e->last_cmd);
	strfree(&e->herestock);
	if (e->env)
		ft_free_tab(e->env);
	if (e->history)
		ft_free_tab(e->history);
	if (e->magic)
		magic_free(e);
	if (e->hdoc_words)
		ft_free_tab(e->hdoc_words);
	free_split_delim(e);
	free(e);
}

void	ft_triple_free(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	if (e->cat)
	{
		while (e->cat[++i])
		{
			j = -1;
			while (e->cat[i][++j])
			{
				free(e->cat[i][j]);
				e->cat[i][j] = NULL;
			}
			free(e->cat[i]);
			e->cat[i] = NULL;
		}
		free(e->cat);
		e->cat = NULL;
	}
}

char	**new_tabcat(char ***oldtab, char **str)
{
	char	**ret;

	ret = ft_tabcat(*oldtab, *str);
	ft_free_tab(*oldtab);
	strfree(str);
	return (ret);
}
