/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:54:04 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/22 15:12:19 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 20
# define MAX_FD 256
# define I_SIZE 2

typedef struct		s_gnl
{
	char			*rline;
}					t_gnl;

int					get_next_line(int const fd, char **line);

#endif
