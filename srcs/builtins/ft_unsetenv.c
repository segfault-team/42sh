/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:05:01 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 16:55:42 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_unsetenv(char ***env, char *name)
{
	size_t	pos;
	char	*nameequ;
	char	**ptr;
	char	**tmp;

	pos = -1;
	ptr = *env;
	nameequ = ft_strjoin(name, "=");
	if (ptr && name)
	{
		while (ptr[++pos])
		{
			if (ft_strnequ(ptr[pos], nameequ, ft_strlen(nameequ)))
			{
				tmp = ft_tabpop(ptr, pos);
				ft_free_tab(*env);
				*env = tmp;
				free(nameequ);
				return (0);
			}
		}
	}
	free(nameequ);
	return (-1);
}

int			ft_unsetenv_blt(t_env *e)
{
	int		i;

	i = 0;
	if (e->cmd_len > 1)
	{
		while (++i < (int)e->cmd_len)
		{
			if (ft_strequ(e->cmd[i], "all"))
			{
				ft_free_tab(e->env);
				e->env = NULL;
			}
			else
				ft_unsetenv(&e->env, e->cmd[i]);
		}
		return (0);
	}
	return (ft_error("unsetenv", "too few arguments", NULL));
}
