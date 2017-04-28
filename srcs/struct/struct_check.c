/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboddez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:50:45 by kboddez           #+#    #+#             */
/*   Updated: 2017/04/28 17:50:45 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**  CHECK IF A REDIRECTION IS IN 'str'
*/

static int	red_strstr_check(char *s, int i)
{
	if (s[i] == '|' && s[i + 1] == '|')
		return (0);
	if (s[i] == '&' && s[i + 1] == '&')
		return (0);
	return (1);
}

int			red_strstr(char *s)
{
	int		i;
	int		bs;
	char	quote;

	i = -1;
	bs = 0;
	quote = '\0';
	while (s[++i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			quote = ft_check_quote_bs(s[i], quote, bs);
			if (!quote && !bs)
			{
				if (!red_strstr_check(s, i))
					return (0);
				if (is_redir_sign(s[i]))
					return (1);
			}
		}
	}
	return (0);
}

/*
**  CHECK IF CURRENT e->magic[i].cmd IS NOT A REDIRECTION
**  OR A FILE FOR REDIRECTION
*/

int			struct_check_cmd(int i, t_env *e)
{
	if (i > 0 && is_redir_pipe(e, i - 1))
		return (1);
	else if (i && !ft_strcmp(e->magic[i - 1].type, "output"))
		return (1);
	else if (i == 0 && !red_strstr(e->magic[i].cmd))
		return (1);
	return (0);
}
