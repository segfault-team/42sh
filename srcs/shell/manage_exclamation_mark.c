#include "shell.h"

static int	gestion_error(char *arg, char *sh_name)
{
	ft_printf("%s: !%s event not found\n", sh_name, arg);
	strfree(&arg);
	return (-1);
}

static int	manage_double_excl_mark(t_env *e, int *curr_pos)
{
	int	i_hist;

	if (!e->history)
		return (gestion_error("!", SH_NAME));
	i_hist = ft_tablen(e->history) - 1;
	do_substitution(e, curr_pos, e->history[i_hist], 1);
	return (1);
}

static int	manage_for_pos_number(t_env *e, int *curr_pos)
{
	int	i_hist;
	int	i;

	i_hist = 0;
	i = *curr_pos;
	while (is_number(e->line[++i]))
		i_hist = i_hist * 10 + (e->line[i] - '0');
	if (!e->history || !e->history[i_hist + 1])
		return (gestion_error(ft_itoa(i_hist), SH_NAME));
	do_substitution(e, curr_pos, e->history[i_hist], i + 2);
	return (1);
}

static int	manage_for_neg_number(t_env *e, int *curr_pos)
{
	int	i_hist;
	int	mem;
	int	i;

	i_hist = 0;
	i = *curr_pos + 1;
	while (is_number(e->line[++i]))
		i_hist = i_hist * 10 + (e->line[i] - '0');
	if (!e->history)
		return (gestion_error(ft_itoa(i_hist), SH_NAME));
	mem = i_hist;
	i_hist = ft_tablen(e->history) - i_hist;
	if (i_hist < 0 || !e->history[i_hist])
		return (gestion_error(ft_itoa(mem), SH_NAME));
	do_substitution(e, curr_pos, e->history[i_hist], i + 3);
	return (1);
}

static int	join_line(t_env *e, int *curr_pos)
{
	char	*new;

	new = ft_strnew(*curr_pos + 1);
	new = ft_strncpy(new, e->line, *curr_pos);
	do_substitution(e, curr_pos, new, 2);
	strfree(&new);
	return (1);
}

static int	manage_for_string(t_env *e, int *curr_pos)
{
	int		i;
	char	*cmp;

	i = *curr_pos + 1;
	while (e->line[i] && e->line[i] != ' ')
		++i;
	cmp = ft_strsub(e->line, *curr_pos + 1, i);
	i = ft_tablen(e->history) - 1;
	while (i && !ft_start_with(e->history[i], cmp))
		--i;
	if (!i && !ft_start_with(e->history[i], cmp))
		return (gestion_error(cmp, SH_NAME));
	do_substitution(e, curr_pos, e->history[i], ft_strlen(cmp));
	strfree(&cmp);
	return (1);
}

int			manage_exclamation_mark(t_env *e, int *curr_pos)
{
	char	nxt_c;

	if (!e->line[*curr_pos + 1])
		// MANAGE '!' alone
		return (-1);
	nxt_c = e->line[*curr_pos + 1];
	if (is_number(nxt_c))
		return (manage_for_pos_number(e, curr_pos));
	else if (nxt_c == '-')
		return (manage_for_neg_number(e, curr_pos));
	else if (nxt_c == '!')
		return (manage_double_excl_mark(e, curr_pos));
	else if (nxt_c == '#')
		return (join_line(e, curr_pos));
	else
		return (manage_for_string(e, curr_pos));
	return (0);
}
