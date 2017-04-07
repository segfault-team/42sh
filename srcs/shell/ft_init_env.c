/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:28 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:28 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int			ft_set_home(t_env *e, char *path)
{
	int				uid;
	char			*login;

	e->home = NULL;
	if ((e->home = ft_getenv(e->env, "HOME")))
		return (1);
	if ((uid = getuid()))
	{
		if ((path = ft_getpath_uid(uid, NULL)))
		{
			e->home = ft_strdup(path);
			ft_setenv(&e->env, "HOME", path);
			return (1);
		}
		if ((login = getlogin()))
		{
			login = ft_strjoin(USERS_DIR, login);
			e->home = ft_strdup(login);
			ft_setenv(&e->env, "HOME", login);
			strfree(&login);
			return (1);
		}
	}
	return (0);
}

void		ft_set_shlvl(t_env *e)
{
	char	*lvl;
	int		tmp;

	if ((lvl = ft_getenv(e->env, "SHLVL")))
	{
		tmp = ft_atoi(lvl) + 1;
		free(lvl);
		lvl = ft_itoa(tmp);
		ft_setenv(&e->env, "SHLVL", lvl);
		free(lvl);
	}
	else
		ft_setenv(&e->env, "SHLVL", "1");
}
