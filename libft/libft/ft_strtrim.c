/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 12:00:18 by lfabbro           #+#    #+#             */
/*   Updated: 2016/09/28 10:45:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** DESCRIPTION:
**     Allocates (with malloc(3)) and returns a copy of the string
**     given as argument without whitespaces at the beginning or at
**     the end of the string. Will be considered as whitespaces the
**     following characters ’ ’, ’\n’ and ’\t’. If s has no whitespaces
**     at the beginning or at the end, the function returns a
**     copy of s. If the allocation fails the function returns NULL.
**
** LEGENDA:
**     cp = copy;
**     cl = cp len;
**     sl = s len;
**     bw = backward skip;
**     fw = forward skip;
*/

static char		*ft_trim_cp(char const *s, int cl, int fw)
{
	char	*cp;
	int		i;

	i = 0;
	if ((cp = ft_strnew(cl)) == NULL)
		return (NULL);
	while (i < cl)
	{
		cp[i] = s[fw];
		++i;
		++fw;
	}
	cp[cl] = '\0';
	return (cp);
}

static int		ft_cp_len(int fw, int bw, int len)
{
	int		cl;

	cl = 0;
	if (bw)
		cl = (len - fw - (len - bw));
	return (cl);
}

char			*ft_strtrim(char const *s)
{
	int		sl;
	int		cl;
	int		bw;
	int		fw;

	if (s)
	{
		sl = ft_strlen(s);
		bw = sl;
		fw = 0;
		while (s[fw] == ' ' || s[fw] == '\n' || s[fw] == '\t')
			++fw;
		while (bw && (s[bw - 1] == ' ' || s[bw - 1] == '\n' || \
					s[bw - 1] == '\t'))
			--bw;
		cl = ft_cp_len(fw, bw, sl);
		return (ft_trim_cp(s, cl, fw));
	}
	return (NULL);
}
