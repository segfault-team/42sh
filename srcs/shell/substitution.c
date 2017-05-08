/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:47 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/08 23:13:45 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	substitution_cond(char **str, int *i, char *tmp)
{
	int		ret;

	tmp = ft_strdup(*str);
	do_substitution(str, i, USERS_DIR, 0);
	if (access(&(*str)[*i], F_OK) == -1)
	{
		ft_strdel(str);
		*str = tmp;
		return (-1);
	}
	ret = ft_strlen(tmp);
	strfree(&tmp);
	return (ret);
}

static int	substitution_tilde(t_env *e, char **str, int i)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	if ((*str)[i] == '~' && (*str)[i + 1] && (*str)[i + 1] != ' '
		&& (*str)[i + 1] != '/' && (*str)[i + 1] != '$' && (i == 0
		|| (*str)[i - 1] == ' '))
	{
		if ((tmp = ft_getpath_login(&(*str)[i + 1])))
			do_substitution(str, &i, tmp, ft_strlen(&(*str)[i + 1]));
		else
			return (substitution_cond(str, &i, tmp));
	}
	else if ((*str)[i] == '~' && (i == 0 || (*str)[i - 1] == ' ')
			&& (!(*str)[i + 1] || ((*str)[i + 1] != '~'
			&& (*str)[i + 1] != '\'' && (*str)[i + 1] != '\"')))
	{
		tmp = ft_getenv(e->env, "HOME");
		if (!tmp)
			tmp = ft_strdup(e->home);
		do_substitution(str, &i, tmp, 0);
	}
	ret = ft_strlen(tmp);
	ft_strdel(&tmp);
	return (ret);
}

int			substitution(t_env *e, char **str, char quote, int bs)
{
	int		i;
	int		len;

	i = -1;
	len = (int)ft_strlen(*str);
	if (!(*str))
		return (0);
	while (str && ++i < len && (*str)[i])
	{
		if (!bs && (*str)[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs((*str)[i], quote, bs);
			if (quote != '\'')
			{
				if (i < len && (*str)[i] == '$' && (*str)[i + 1])
					do_env_subs(e, str, &i);
				else
					substitution_tilde(e, str, i);
				len = (int)ft_strlen(*str);
			}
		}
	}
	return (0);
}
