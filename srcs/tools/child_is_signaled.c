/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_is_signaled.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 21:35:16 by vlistrat          #+#    #+#             */
/*   Updated: 2017/05/08 21:35:17 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		child_is_signaled(int status)
{
	if (status > 0)
		return (WTERMSIG(status));
	return (0);
}
