#include "shell.h"

static int	manage_for_pos_number(t_env *e, int *curr_pos, int y, int z)
{
	long long int	i_hist;
	int				i;
	int				len;

	i_hist = 0;
	i = *curr_pos;
	len = 0;
	while (e->cat[y][z][++i] && is_number(e->cat[y][z][i]))
	{
		++len;
		i_hist = i_hist * 10 + (e->cat[y][z][i] - '0');
	}
	if (!e->history || i_hist < 0
		|| (e->history && i_hist < (int)ft_tablen(e->history)
		&& !e->history[i_hist + 1]) || i_hist > 2147483647)
		return (error_em(ft_strsub(e->cat[y][z], *curr_pos + 1, len - 1), SH_NAME));
	do_substitution(&e->cat[y][z], curr_pos, e->history[i_hist], i + 2);
	return (1);
}

static int	manage_for_neg_number(t_env *e, int *curr_pos, int y, int z)
{
	int	i_hist;
	int	i;
	int	len;

	len = 0;
	i_hist = 0;
	i = *curr_pos + 1;
	while (is_number(e->cat[y][z][++i]))
	{
		i_hist = i_hist * 10 + (e->cat[y][z][i] - '0');
		++len;
	}
	if (!e->history || i_hist < 0 || i_hist > 2147483647)
		return (error_em(ft_strsub(e->cat[y][z], *curr_pos + 1, len - 1), SH_NAME));
	i_hist = (int)ft_tablen(e->history) - i_hist;
	if (!e->history || i_hist < 0 || i_hist > 2147483647)
		return (error_em(ft_strsub(e->cat[y][z], *curr_pos + 1, len - 1), SH_NAME));
	if (i_hist > (int)ft_tablen(e->history) || !e->history[i_hist + 1])
		return (error_em(ft_strsub(e->cat[y][z], *curr_pos + 1, len - 1), SH_NAME));
	do_substitution(&e->cat[y][z], curr_pos, e->history[i_hist], i + 3);
	return (1);
}

static int	manage_for_string(t_env *e, int *curr_pos, int y, int z)
{
	int		i;
	char	*cmp;

	i = *curr_pos + 1;
	while (e->cat[y][z][i] && e->cat[y][z][i] != ' ')
		++i;
	cmp = ft_strsub(e->cat[y][z], *curr_pos + 1, i);
	i = ft_tablen(e->history) - 1;
	while (i && !ft_start_with(e->history[i], cmp))
		--i;
	if (!i && !ft_start_with(e->history[i], cmp))
		return (error_em(cmp, SH_NAME));
	do_substitution(&e->cat[y][z], curr_pos, e->history[i], ft_strlen(cmp));
	strfree(&cmp);
	return (1);
}

int			manage_exclamation_mark(t_env *e, int *curr_pos, int y, int z)
{
	char	nxt_c;

	if (!e->cat[y][z][*curr_pos + 1])
		return (-1);
	nxt_c = e->cat[y][z][*curr_pos + 1];
	if (is_number(nxt_c))
		return (manage_for_pos_number(e, curr_pos, y, z));
	else if (nxt_c == '-')
		return (manage_for_neg_number(e, curr_pos, y, z));
	else if (nxt_c == '!')
		return (manage_double_excl_mark(e, curr_pos, y, z));
	else if (nxt_c == '#')
		return (join_line(e, curr_pos, y, z));
	else
		return (manage_for_string(e, curr_pos, y, z));
	return (0);
}
