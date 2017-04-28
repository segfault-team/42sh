/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/28 12:07:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_prompt(char *prompt)
{
	ft_putstr(GREEN);
	ft_putstr(prompt);
	ft_putstr(ENDC);
}

static char	*ft_getdir(char *str)
{
	int		len;
	char	*ptr;

	len = ft_strlen(str);
	while (str[len] != '/')
		len--;
	ptr = ft_strdup(&str[len + 1]);
	if (!*ptr)
		*ptr = '/';
	return (ptr);
}

char		*ft_create_prompt(t_env *e, char *prompt)
{
	char	*new_prompt;
	char	*tmp;
	char	str[255];
	char	*pattern;

	if ((pattern = ft_getenv(e->env, "PROMPT")))
		substitution(e, &pattern, '\0', 0);
	if (!(new_prompt = ft_getenv(e->env, "PWD")))
		new_prompt = ft_strdup(getcwd(str, 255));
	tmp = ft_getdir(new_prompt);
	ft_strdel(&new_prompt);
	new_prompt = ft_strjoin(tmp, prompt);
	ft_strdel(&tmp);
	strfree(&e->prompt);
	if (pattern)
	{
		tmp = new_prompt;
		new_prompt = ft_strjoin(pattern, tmp);
		ft_strdel(&tmp);
		ft_strdel(&pattern);
	}
	return (new_prompt);
}
