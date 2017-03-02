/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 20:03:34 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/02 17:46:48 by lfabbro          ###   ########.fr       */a
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_matchquotes(char *s)
{
	int		i;
	int		bs;
	char	quote;

	i = 0;
	bs = 0;
	quote = '\0';
	while (s[i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			bs = 0;
		}
		++i;
	}
	if (quote != '\0')
		return (0);
	return (1);
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
	tmp = NULL;
	if ((tmp = ft_issetenv(env, name)) != NULL)
	{
		value = ft_strdup(ft_strchr(tmp, '=') + 1);
	}
	return (value);
}
