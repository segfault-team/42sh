#include "shell.h"

static int	manage_for_pos_number(t_env *e, int *curr_pos)
{
	long long int	i_hist;
	int				i;
	int				len;

	i_hist = 0;
	i = *curr_pos;
	len = 0;
	while (e->line[++i] && is_number(e->line[i]))
	{
		++len;
		i_hist = i_hist * 10 + (e->line[i] - '0');
	}
	if (!e->history || i_hist < 0
		|| (e->history && i_hist > (int)ft_tablen(e->history))
		|| i_hist > 2147483647)
		return (error_em(ft_strsub(e->line, *curr_pos + 1, len), SH_NAME));
	do_substitution(&e->line, curr_pos, e->history[i_hist], len);
	return (1);
}

static int	manage_for_neg_number(t_env *e, int *curr_pos)
{
	int	i_hist;
	int	i;
	int	len;

	len = 0;
	i_hist = 0;
	i = *curr_pos + 1;
	while (is_number(e->line[++i]))
	{
		i_hist = i_hist * 10 + (e->line[i] - '0');
		++len;
	}
	if (!e->history || i_hist < 0 || i_hist > 2147483647)
		return (error_em(ft_strsub(e->line, *curr_pos + 1, len - 1), SH_NAME));
	i_hist = (int)ft_tablen(e->history) - i_hist;
	if (!e->history || i_hist < 0 || i_hist > 2147483647)
		return (error_em(ft_strsub(e->line, *curr_pos + 1, len - 1), SH_NAME));
	if (i_hist > (int)ft_tablen(e->history) || !e->history[i_hist + 1])
		return (error_em(ft_strsub(e->line, *curr_pos + 1, len - 1), SH_NAME));
	do_substitution(&e->line, curr_pos, e->history[i_hist], len);
	return (1);
}

static int	manage_for_string(t_env *e, int *curr_pos)
{
	int		start;
	int		i;
	char	*cmp;

	start = *curr_pos + 1;
	i = 0;
	while (e->line[start + i] && e->line[start + i] != ' '
		&& (!i || (e->line[start + i] == '\'' && e->line[start + i] == '\"'))
		&& !ft_is_escape_after(e->line, start + i))
		i++;
	cmp = ft_strsub(e->line, start, i);
	i = ft_tablen(e->history) - 1;
	while (cmp && i && !ft_start_with(e->history[i], cmp))
		--i;
	if (!cmp || (!i && !ft_start_with(e->history[i], cmp)))
		return (error_em(cmp, SH_NAME));
	do_substitution(&e->line, curr_pos, e->history[i], ft_strlen(cmp));
	strfree(&cmp);
	return (1);
}

int			manage_exclamation_mark(t_env *e, int *curr_pos)
{
	char	nxt_c;

	if (!e->line[*curr_pos + 1])
		return (-1);
	nxt_c = e->line[*curr_pos + 1];
	if (is_number(nxt_c))
		return (manage_for_pos_number(e, curr_pos));
	else if (nxt_c == '-' && is_number(e->line[*curr_pos + 2]))
		return (manage_for_neg_number(e, curr_pos));
	else if (nxt_c == '!')
		return (manage_double_excl_mark(e, curr_pos));
	else if (nxt_c == '#')
		return (join_line(e, curr_pos));
	else
		return (manage_for_string(e, curr_pos));
	return (0);
}
