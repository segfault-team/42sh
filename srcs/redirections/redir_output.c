/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:54 by vlistrat          #+#    #+#             */
/*   Updated: 2017/05/08 21:43:06 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_dupp(t_env *e)
{
	dup2(FD.stdin, STDIN_FILENO);
	dup2(FD.stdout, STDOUT_FILENO);
	dup2(FD.stderr, STDERR_FILENO);
	return (1);
}

int			ft_redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) != -1)
		{
			if (close(oldfd) < 0)
				return (ft_error(NULL, "Failed closing fd", NULL));
		}
		else
			return (ft_error(NULL, "dup2 failed", NULL));
	}
	return (0);
}

int			ft_redirect_blt(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
			return (ft_error(NULL, "dup2 failed", NULL));
	}
	return (0);
}

int			ft_redir_builtin(t_env *e)
{
	if (redir_check_red(e, "|") || redir_check_red(e, ">") || \
			redir_check_red(e, ">>"))
	{
		if (ft_redirect_blt(FD.in, STDIN_FILENO) ||
				ft_redirect_blt(FD.fd[1], STDOUT_FILENO))
			return (-1);
	}
	return (0);
}
