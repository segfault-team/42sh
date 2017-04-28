/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:09:14 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:09:14 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_insert_arg(char ***env_cpy, char *arg)
{
	char	*name;
	char	*val;

	val = ft_strdup(ft_strchr(arg, '=') + 1);
	name = ft_strndup(arg, (ft_strlen(arg) - ft_strlen(val) - 1));
	ft_setenv(env_cpy, name, val);
	strfree(&val);
	strfree(&name);
	return (0);
}

int			ft_env_error(char *cmd)
{
	ft_printfd(2, "env: illegal option --%c\n", cmd[1]);
	ft_printfd(2, "usage: env [-i] [-u name]\n");
	ft_printfd(2, "           [name=value] [utility [argument ...]]\n");
	return (-1);
}

int			ft_env_opt_u_error(char *cmd)
{
	if (!cmd)
	{
		ft_printfd(2, "env: option requires an argument -- u\n");
		ft_printfd(2, "usage: env [-i] [-u name]\n");
		ft_printfd(2, "           [name=value] [utility [argument ...]]\n");
	}
	else if (cmd)
		ft_printfd(2, "env: unsetenv %s: invalid argument", cmd);
	return (-1);
}
