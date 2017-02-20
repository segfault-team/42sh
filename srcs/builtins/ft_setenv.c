/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:16:46 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/16 09:33:28 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*ft_setentry(char *name, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	entry = ft_strjoin(tmp, value);
	strfree(&tmp);
	return (entry);
}

int				ft_setenv(char ***env, char *name, char *value)
{
	int		i;
	char	*entry;
	char	**tmp;
	char	*nameequ;

	i = -1;
	entry = ft_setentry(name, value);
	nameequ = ft_strjoin(name, "=");
	tmp = *env;
	if (tmp)
		while (tmp[++i])
		{
			if (ft_strnequ(tmp[i], nameequ, ft_strlen(nameequ)))
			{
				strfree(&nameequ);
				strfree(&tmp[i]);
				tmp[i] = entry;
				return (0);
			}
		}
	strfree(&nameequ);
	*env = ft_tabcat(*env, entry);
	strfree(&entry);
	ft_free_tab(tmp);
	return (0);
}

int				ft_setenv_blt(t_env *e)
{
	if (e->cmd_len == 3)
	{
		if (ft_isalpha_str(e->cmd[1]))
		{
			if (!ft_issetenv(e->env, "HOME") && e->home == NULL && \
					ft_strequ(e->cmd[1], "HOME"))
				e->home = ft_strdup(e->cmd[2]);
			return (ft_setenv(&e->env, e->cmd[1], e->cmd[2]));
		}
		return (ft_error("setenv", \
					"variable name must contain only alphanumerics", NULL));
	}
	return (ft_error("setenv", "wrong number of arguments", NULL));
}
