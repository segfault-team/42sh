/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_iteration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:29:14 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:29:14 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	FIND THE NEXT REDIRECTION IF THERE IS ONE
*/

void	struct_find_red(t_env *e)
{
	++(RED_INDEX);
	if (RED_INDEX >= e->len_mag)
		return ;
	while (e->magic[RED_INDEX].cmd
			&& ft_strcmp(e->magic[RED_INDEX].type, "red")
			&& !is_operator(e, RED_INDEX))
		++(RED_INDEX);
}

/*
**	CHECK SI red EST L'ACTUELLE REDIRECTION
*/

int		redir_check_red(t_env *e, char *red)
{
	if (RED_INDEX >= e->len_mag)
		return (0);
	if (e->magic[RED_INDEX].cmd && red &&
			!ft_strcmp(e->magic[RED_INDEX].cmd, red))
		return (1);
	return (0);
}

/*
**	CONTENUE DE L'ITERATION DE e->cat[i] (contient les cmds split par "red")
*/

int		redir_exec_open(int i, t_env *e)
{
	int		ret;

	ret = 0;
	if (pipe(FD.fd) < 0)
		return (ft_error(NULL, "Pipe failed.", NULL));
	struct_find_red(e);
	ret = ft_exec_cmd(e, e->cat[i]);
	FD.in = FD.fd[0];
	return (ret);
}
