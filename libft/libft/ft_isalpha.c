/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:32:56 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/21 10:50:08 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int c)
{
	if (c >= 0 && c <= 127)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
	return (0);
}
