/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_is_signaled.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:10:38 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/04 14:43:13 by lfabbro          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "shell.h"

int		child_is_signaled(int status)
{
	if (status > 0)
		return (WTERMSIG(status));
	return (0);
}
