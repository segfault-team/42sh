/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:16:46 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/15 16:40:17 by lfabbro          ###   ########.fr       */
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
				return (1);
			}
		}
	strfree(&nameequ);
	*env = ft_tabcat(*env, entry);
	strfree(&entry);
	ft_free_tab(tmp);
	return (1);
}

static int		valid_name(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!i && ft_isdigit(s[i]))
			return (ft_error("setenv", \
						"variable name must begin with a letter", NULL));
		else if (!ft_isalnum(s[i]))
			return (ft_error("setenv", \
						"variable name must contain only alphanumerics", NULL));
	}
	return (0);
}

int				ft_setenv_blt(t_env *e, char **cmd)
{
	size_t	len;

	if ((len = ft_tablen(cmd)) == 1)
		return (ft_error("setenv", "wrong number of arguments", NULL));
	if (len > 1 && !valid_name(cmd[1]))
	{
		if (len == 3)
		{
			if (!ft_issetenv(e->env, "HOME") && e->home == NULL && \
					ft_strequ(e->cmd[1], "HOME"))
				e->home = ft_strdup(e->cmd[2]);
			return (ft_setenv(&e->env, cmd[1], cmd[2]));
		}
		return (ft_error("setenv", "wrong number of arguments", NULL));
	}
	return (-1);
}
