/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:05:01 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/05 21:44:35 by lfabbro          ###   ########.fr       */
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
				strfree(&nameequ);
				return (0);
			}
		}
	}
	strfree(&nameequ);
	return (-1);
}

int			ft_unsetenv_blt(t_env *e, char **cmd)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_tablen(cmd);
	if (len > 1)
	{
		while (++i < (int)len)
		{
			// we can probably get rid of that (all) ...
			if (ft_strequ(cmd[i], "all"))
			{
				ft_free_tab(e->env);
				e->env = NULL;
			}
			else
				ft_unsetenv(&e->env, cmd[i]);
		}
		return (0);
	}
	return (ft_error("unsetenv", "too few arguments", NULL));
}
