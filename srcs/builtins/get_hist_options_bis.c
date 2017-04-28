#include "shell.h"

int		manage_opt_hist_priority(t_opt_hist *opt)
{
	int	mem;

	if (opt->a + opt->r + opt->w > 1)
		return (ft_error("history", "cannot use more than one of -arw", NULL));
	if (opt->c)
	{
		init_opt_hist(opt);
		opt->c = 1;
	}
	else if (opt->d)
	{
		mem = opt->i_opt_d;
		init_opt_hist(opt);
		opt->d = 1;
		opt->i_opt_d = mem;
	}
	return (1);
}

int		is_valid_opt(char c)
{
	return ((c == 'a' || c == 'c' || c == 'd' || c == 'h'
			|| c == 'w' || c == 'r' || c == 'p'));
}

void	add_opt(t_opt_hist *opt, char c, int *opt_d, int i)
{
	if (c == 'a')
		opt->a = 1;
	else if (c == 'c')
		opt->c = 1;
	else if (c == 'd')
	{
		*opt_d = 1;
		opt->i_opt_d = i + 1;
		opt->d += 1;
	}
	else if (c == 'h')
		opt->h = 1;
	else if (c == 'w')
		opt->w = 1;
	else if (c == 'r')
		opt->r = 1;
	else if (c == 'p')
		opt->p = 1;
}
