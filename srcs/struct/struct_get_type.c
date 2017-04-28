/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_get_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:50:48 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:50:48 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		struct_arg_red(int i, t_env *e)
{
	int	len;

	if (i > 0 && (!ft_strcmp("|", e->magic[i - 1].cmd) ||
				!ft_strcmp(e->magic[i - 1].type, "cmd") ||
				!ft_strcmp(e->magic[i - 1].type, "heredoc")) &&
		is_next_redir(e, i) != AGGREGATOR)
		e->magic[i].type = ft_strdup("cmd");
	else if (i > 0 && ft_check_input(i - 1, e))
		e->magic[i].type = ft_strdup("input");
	else if (i > 0 && ft_check_heredoc(i - 1, e))
		e->magic[i].type = ft_strdup("heredoc");
	else if (i > 0 && ft_check_output(i - 1, e))
		e->magic[i].type = ft_strdup("output");
	else if ((is_only_numbers(e->magic[i].cmd) ||
				!ft_strcmp(e->magic[i].cmd, "-")) && i && e->magic[i - 1].cmd)
	{
		len = (int)ft_strlen(e->magic[i - 1].cmd) - 1;
		if (e->magic[i - 1].cmd[len] == '>' || e->magic[i - 1].cmd[len] == '>')
			e->magic[i].type = ft_strdup("fd_aggregator");
		else
			e->magic[i].type = ft_strdup("cmd");
	}
	else
		e->magic[i].type = ft_strdup("cmd");
}

/*
**     REMPLIT LE TABLEAU DE STRUCTURE MAGIC ET ASSOCIE CHAQUE ELEMENTS
**     DE LA CMD AVEC LE TYPE DE L'ELEM. EX: ls -l > test
**  	ls  -> "cmd"
**  	-l  -> "cmd"
**  	>   -> "red"
**  	test    -> "output"
*/

int			magic_type(t_env *e)
{
	int i;

	i = -1;
	while (e->magic[++i].cmd)
	{
		if (red_strstr(e->magic[i].cmd))
			e->magic[i].type = ft_strdup("red");
		else if (!ft_strcmp(e->magic[i].cmd, "||")
					|| !ft_strcmp(e->magic[i].cmd, "&&"))
			e->magic[i].type = ft_strdup("operator");
		else if (struct_check_cmd(i, e))
			e->magic[i].type = ft_strdup("cmd");
		else
			struct_arg_red(i, e);
	}
	magic_realloc(e);
	return (check_magic_red(e));
}
