/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 14:30:30 by lfabbro           #+#    #+#             */
/*   Updated: 2017/04/07 14:30:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	open_file(char *file, int flags, mode_t mode)
{
	int	fd;

	if (access(file, F_OK) < 0)
		return (ft_error("no such file: ", file, NULL));
	if (access(file, R_OK) < 0)
		return (ft_error("permission denied: ", file, NULL));
	if ((fd = open(file, flags, mode)) == -1)
		return (ft_error(file, "Resource temporarily unavailable", NULL));
	return (fd);
}
