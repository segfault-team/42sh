/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_to_aggregator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:43:55 by vlistrat          #+#    #+#             */
/*   Updated: 2017/04/28 18:43:55 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define ERROR		 	-1
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1
#define ERROR_FILENUMBER -4242

/*
** fd_tab[0] = fd_src
** fd_tab[1] = fd_dst
** fd_tab[2] = ag_type
** fd_tab[3] = is_file
*/

static int	aggregator_error(int id, char *sh_name)
{
	if (id == 1)
		ft_printfd(STDERR_FILENO, "%s: bad file descriptor\n", sh_name);
	else if (id == ERROR_FILENUMBER)
		ft_printfd(STDERR_FILENO, "%s: file number expected\n", sh_name);
	else
		ft_printfd(STDERR_FILENO, "%s: redirection syntax error\n", sh_name);
	return (-1);
}

static int	is_valid_src(int fd)
{
	if (fd >= 0)
		return (1);
	if (fd < 0 && !isatty(fd))
		return (0);
	return (1);
}

static int	is_valid_dst(int fd)
{
	if (!fd || fd == 1 || fd == 2 || fd == -42)
		return (1);
	if (!isatty(fd))
		return (0);
	return (1);
}

static int	redir_to_aggregator_bis(t_env *e, int fd_tab[4])
{
	if (fd_tab[2] == ERROR)
		return (-1);
	else if (fd_tab[1] == -42)
		close_aggre(e, fd_tab[0]);
	else if (fd_tab[2] == INPUT_AGGRE)
		dup2(fd_tab[0], fd_tab[1]);
	else
		output_aggre(e, fd_tab[0], fd_tab[1], fd_tab[3]);
	return (1);
}

int			redir_to_aggregator(t_env *e)
{
	int		fd_tab[4];

	fd_tab[0] = isolate_fd_source(e);
	fd_tab[1] = isolate_fd_destination(e, &fd_tab[3]);
	if (fd_tab[1] == ERROR_FILENUMBER)
		return (aggregator_error(ERROR_FILENUMBER, SH_NAME));
	if (fd_tab[3] && fd_tab[1] == -1)
		return (-1);
	else if (!is_valid_src(fd_tab[0])
			|| (!is_valid_dst(fd_tab[1]) && !fd_tab[3]))
		return (aggregator_error(1, SH_NAME));
	fd_tab[2] = find_aggregator_type(e);
	if (fd_tab[1] == ERROR || (fd_tab[0] == ERROR && fd_tab[2] == OUTPUT_AGGRE))
		return (aggregator_error(42, SH_NAME));
	if (redir_to_aggregator_bis(e, fd_tab) < 0)
		return (-1);
	if (fd_tab[3])
		close(fd_tab[1]);
	return (1);
}
