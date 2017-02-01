/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:03:34 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/01 15:12:24 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_matchquotes(char *s)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (s[i])
	{
		if (quote != '\0' && s[i] == quote)
			quote = '\0';
		else if (quote == '\0' && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		++i;
	}
	if (quote != '\0')
		return (quote);
	return (0);
}

void		ft_env_free(t_env *e)
{
	if (e->line)
		free(e->line);
	if (e->home)
		free(e->home);
	if (TCAPS.term_name)
		free(TCAPS.term_name);
// DOUBLE FREE ??
//	if (e->history)
//		ft_free_tab(e->history);
	if (e->prompt)
		free(e->prompt);
	if (e->env)
		ft_free_tab(e->env);
}

char		*ft_issetenv(char **env, char *name)
{
	char	*eval;
	int		i;

	i = -1;
	eval = ft_strjoin(name, "=");
	if (env)
	{
		while (env[++i])
		{
			if (ft_strnequ(env[i], eval, ft_strlen(eval)))
			{
				free(eval);
				return (env[i]);
			}
		}
	}
	free(eval);
	return (NULL);
}

char		*ft_getenv(char **env, char *name)
{
	char	*value;
	char	*tmp;

	value = NULL;
	if ((tmp = ft_issetenv(env, name)) != NULL)
	{
		value = ft_strdup(ft_strchr(tmp, '=') + 1);
//		free(tmp);
	}
	return (value);
}

/*
** RAZ LE CUL DE TOUT REECRIRE !
*/

void	xputs(char *tag)
{
	char	*res;

	res = tgetstr(tag, NULL);
	tputs(res, 1, dsh_putchar);
}

void	move_right(t_env *e)
{
	if (TCAPS.nb_col == (WS_COL - 1))
	{
		xputs("do");
		xputs("cr");
	}
	else
		xputs("nd");
	++TCAPS.nb_move;
	tcaps_recalc_pos(e);
}
