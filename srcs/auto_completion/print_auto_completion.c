/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_auto_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:10:10 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/28 18:10:10 by aleghmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		write_line(t_env *e, int i, int x, char *spaces)
{
	int len;
	int moar;

	moar = 0;
	while (i < e->c_match)
	{
		moar = (int)ft_strlen(e->files[i]->name) > e->tcaps.ws.ws_col ?
			moar + 1 : moar;
		if ((len = (int)e->total_len - (int)ft_strlen(e->files[i]->name)) < 0)
			len = 0;
		if ((i + 4) <= e->c_match)
			spaces[0] = ' ';
		spaces[len] = '\0';
		if (ft_strlen(e->files[i]->name) >= e->tcaps.ws.ws_col)
			spaces[0] = '\0';
		ft_put_file(e, i, spaces);
		spaces[len] = ' ';
		i += x;
	}
	return (moar);
}

void	ft_putstr_spec(t_env *e, char *str)
{
	int tmp;

	tmp = NB_MOVE;
	ft_putstr(str);
	NB_MOVE = ft_strlen(str);
	while (NB_MOVE--)
		xputs(TGETSTR_LE);
	NB_MOVE = tmp;
}

void	actual_print(t_env *e, int i, int moar)
{
	char	*tmp;

	tmp = ft_strnew(e->total_len + 4);
	tmp = ft_memset(tmp, ' ', e->total_len + 2);
	xputs(e->struct_tputs.cd);
	while (i < e->row && (i - e->start) < e->tcaps.ws.ws_row - 1 - moar)
	{
		ft_putchar('\n');
		moar += write_line(e, i, e->row, tmp);
		i++;
	}
	ft_strdel(&tmp);
	while ((i + moar) - e->start)
	{
		xputs(e->struct_tputs.up);
		i--;
	}
	i = NB_MOVE;
	tcaps_ctrl_home(e);
	while (NB_MOVE < i)
		move_right(e);
}

void	pre_print(t_env *e)
{
	e->printed = -1;
	e->row = calc_rows(e);
	actual_print(e, e->start, 0);
	if (e->selected >= 0)
		ft_putstr(e->files[e->selected]->name);
	xputs(e->struct_tputs.ce);
	ft_putstr_spec(e, &e->line[NB_MOVE]);
	if (e->printed < 0 && e->selected >= 0)
	{
		e->start = e->start + 1 < e->row ? e->start + 1 : 0;
		pre_print(e);
	}
}

void	print_auto_completion(t_env *e, char *arg, char *path, char **content)
{
	if (content)
	{
		e->path = ft_strjoin(path, "/");
		ft_strdel(&path);
		e->prefix = arg;
		e->files = (t_file **)malloc((ft_tablen(content) + 1)
			* sizeof(t_file*));
		e->files[ft_tablen(content)] = NULL;
		ft_fill_files(content, e);
		ft_free_tab(content);
	}
	if (e->c_match == 1)
	{
		e->selected = 0;
		valid_selection(e);
	}
	pre_print(e);
}
