#include "shell.h"


static int	gestion_error(char *arg, char *sh_name)
{
	ft_printf("%s: !%s event not found\n", sh_name, arg);
	return (-1);
}
/*static int    is_valid_mark(char *line, int i)
  {

  }

  // in manage_exclamation_mark
  if (!is_valid_mark(e->line, *curr_pos))
  return ;
*/




static int	manage_for_pos_number(t_env *e, int *curr_pos)
{
	int	arg;
	int	i;

	arg = 0;
	i = *curr_pos;
	while (isNumber(e->line[++i]))
		arg = arg * 10 + (e->line[i] - '0');
	if (!e->history || !e->history[arg + 1])
		return (gestion_error(ft_itoa(arg), SH_NAME));
	do_substitution(e, curr_pos, e->history[arg], i + 2);
	return (1);
}

static int	manage_for_neg_number(t_env *e, int *curr_pos)
{
	int	arg;
	int	mem;
	int	i;

	arg = 0;
	i = *curr_pos + 1;
	while (isNumber(e->line[++i]))
		arg = arg * 10 + (e->line[i] - '0');
	if (!e->history)
		return (gestion_error(ft_itoa(arg), SH_NAME));
	mem = arg;
	arg = ft_tablen(e->history) - arg;
	if (arg < 0 || !e->history[arg])
		return (gestion_error(ft_itoa(mem), SH_NAME));
	do_substitution(e, curr_pos, e->history[arg], i + 3);
	return (1);
}

int 		manage_exclamation_mark(t_env *e, int *curr_pos)
{
	char    nxt_c;

	if (!e->line[*curr_pos + 1])
		// MANAGE '!' alone
		return (-1);
	nxt_c = e->line[*curr_pos + 1];
	if (isNumber(nxt_c))
		return (manage_for_pos_number(e, curr_pos));
	else if (nxt_c == '-')
		return (manage_for_neg_number(e, curr_pos));
	return (-1);
//	else if (nxt_c == '#')
//		join_line(e, *curr_pos);
//	else
//		manage_for_string(e, *curr_pos);
}
