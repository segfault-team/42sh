/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_subs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:10 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:07:10 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	*gestion_error(char *sh_name, char *s1, int id)
{
	if (!id)
		ft_printfd(2, "%s: Unmatched Parenthesis", sh_name, s1);
	return (NULL);
}

static char	*isolate_var_name(char *sh_name, char *line, int i)
{
	int		tmp;

	tmp = i;
	if (!line[i])
		return (gestion_error(sh_name, NULL, 0));
	while (line[tmp] && line[tmp] != '/' && line[tmp] != ' '
			&& line[tmp] != '$' && line[tmp] != '\''
			&& line[tmp] != '\"' && line[tmp] != '\\')
		++tmp;
	return (ft_strsub(line, i, (tmp - i)));
}

int			do_env_subs(t_env *e, char **target, int *curr_pos)
{
	char	*var;
	char	*substi;

	if (!(var = isolate_var_name(SH_NAME, *target, *curr_pos + 1)))
		return (-1);
	if (!ft_strcmp(var, "?"))
		substi = ft_strdup(e->last_ret);
	else
		substi = ft_getenv(e->env, var);
	do_substitution(target, curr_pos, substi, (int)ft_strlen(var));
	strfree(&var);
	strfree(&substi);
	return (ft_strlen(substi));
}
