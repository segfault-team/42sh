/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_substitution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:07 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:07:07 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*pre_substitution(char **new, char **ret, char *target, int len)
{
	*new = ft_strnew((int)(ft_strlen(target) + len));
	*ret = *new;
	return (target);
}

static void	simple_replace(char **new, char **target)
{
	**new = **target;
	++(*new);
}

void		do_substitution(char **target, int *curr_pos, char *substitute,
							int jmp)
{
	char	*new;
	char	*tmp;
	char	*ret;
	int		escape;

	escape = **target != '!' ? 1 : 0;
	tmp = pre_substitution(&new, &ret, *target, (int)ft_strlen(substitute));
	while (((*target)) && **target)
	{
		if (*target == &tmp[*curr_pos])
			(!substitute) ? *target += jmp
				: ft_replace_word(&new, substitute, &*target, jmp + 1);
		else
			simple_replace(&new, target);
		(*target)++;
	}
	*target = substitute && escape
	? escape_specials(ret, *curr_pos, ft_strlen(substitute)) : ft_strdup(ret);
	ft_strdel(&ret);
	ft_strdel(&tmp);
}

void		do_substitution_no_esc(char **target, int *curr_pos,
		char *substitute, int jmp)
{
	char	*new;
	char	*tmp;
	char	*ret;

	tmp = pre_substitution(&new, &ret, *target, (int)ft_strlen(substitute));
	while (((*target)) && **target)
	{
		if (*target == &tmp[*curr_pos])
			(!substitute) ? *target += jmp
				: ft_replace_word(&new, substitute, &*target, jmp + 1);
		else
			simple_replace(&new, target);
		(*target)++;
	}
	*target = ft_strdup(ret);
	ft_strdel(&ret);
	ft_strdel(&tmp);
}
