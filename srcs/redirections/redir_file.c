/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:52 by vlistrat          #+#    #+#             */
/*   Updated: 2017/05/10 16:57:00 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				find_last_pipe(t_env *e)
{
	int		tmp;

	if (!RED_INDEX || RED_INDEX >= e->len_mag || !e->magic[0].cmd
			|| !e->magic[RED_INDEX].cmd)
		return (RED_INDEX);
	tmp = RED_INDEX;
	while (--tmp)
		if (is_redir_pipe(e, tmp) || is_operator(e, tmp)
				|| !ft_strcmp(e->magic[tmp].cmd, ";"))
			return (tmp);
	return (0);
}

int				find_next_output(t_env *e, int i)
{
	if (i >= (int)e->len_mag || !e->magic[0].cmd
			|| !e->magic[i].cmd)
		return (0);
	if (!e->magic[i].cmd)
		return (0);
	while (e->magic[++i].cmd && !is_redir_pipe(e, i) && !is_operator(e, i)
			&& ft_strcmp(e->magic[i].cmd, ";"))
	{
		if (is_output_redir(e, i))
			return (i);
	}
	return (0);
}

static void		redir_output_do(t_env *e, int fd, int i, char *out)
{
	int		red;

	red = ft_strcmp(e->magic[i].cmd, ">>");
	if ((fd = open(e->magic[i + 1].cmd,
		(!red ? TWO_RED_FLAGS : ONE_RED_FLAGS), OFLAGS)) > -1)
	{
		ft_printfd(fd, "%s", out ? out : "");
		if (out && out[(int)ft_strlen(out) - 1] != '\n')
			ft_printfd(fd, "\n");
		ft_close(fd);
	}
	else
		ft_error("failed opening file",\
			e->magic[i + 1].cmd ? e->magic[i + 1].cmd : NULL, NULL);
}

static int		redir_file_output(t_env *e, char *ret_output)
{
	int		fd_output;
	int		i;

	i = find_last_pipe(e);
	fd_output = 0;
	while (e->magic[++i].cmd && !is_redir_pipe(e, i) && !is_operator(e, i))
		if (is_output_redir(e, i))
			redir_output_do(e, fd_output, i, ret_output);
	strfree(&ret_output);
	if (is_next_redir(e, RED_INDEX) != INPUT)
		struct_find_red(e);
	return (1);
}

int				redir_fill_output(t_env *e)
{
	char	*ret_output;
	char	tmp[4096];
	char	*tmp_join;
	int		len;

	tmp_join = NULL;
	ret_output = NULL;
	ft_bzero(tmp, 4095);
	while ((len = read(FD.in, &tmp, 4095)) > 0)
	{
		tmp[len] = '\0';
		if (!ret_output)
			ret_output = ft_strdup(tmp);
		else if ((tmp_join = ft_strjoin(ret_output, tmp)))
		{
			strfree(&ret_output);
			ret_output = tmp_join;
		}
	}
	return (redir_file_output(e, ret_output));
}
