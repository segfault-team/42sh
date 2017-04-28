/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections_part4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:46 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:46 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_last_cmd(t_env *e, int i)
{
	while (i < (int)e->len_mag && e->magic[i].cmd
			&& !is_redir_pipe(e, i)
			&& !is_operator(e, i))
		++i;
	if ((i == (int)e->len_mag && !e->magic[i].cmd)
		|| (i < (int)e->len_mag && e->magic[i].cmd && is_operator(e, i)))
		return (1);
	return (0);
}

int		is_output_after(t_env *e, int i)
{
	while (i <= (int)e->len_mag && e->magic[i].cmd
			&& !is_redir_pipe(e, i) && !is_operator(e, i)
			&& !is_output_redir(e, i))
		++i;
	if (is_output_redir(e, i))
		return (1);
	return (0);
}
