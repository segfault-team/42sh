#include "shell.h"

static int	manage_opt_hist_priority(t_opt_hist *opt)
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

static int	is_valid_opt(char c)
{
	return ((c == 'a' || c == 'c' || c == 'd' || c == 'h'
				|| c == 'w' || c == 'r' || c == 'p'));
}

static void	add_opt(t_opt_hist *opt, char c, int *opt_d, int i)
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

static int	manage_suspend_opt(int i, char **cmd, t_opt_hist *opt)
{
	if (cmd[i + 1])
		if (!is_only_numbers(cmd[i + 1]))
			return (ft_error("history", cmd[1 + 1], "numeric argument required"));
	return (manage_opt_hist_priority(opt));
}

static int	get_opt_in_one_arg(int i, char **cmd, t_opt_hist *opt)
{
	int		j;
	int		len;
	int		opt_d;
	char	tmp[2];

	len = (int)ft_tablen(cmd);
	j = -1;
	while (cmd[i][++j])
	{
		opt_d = 0;
		if (is_valid_opt(cmd[i][j]))
			add_opt(opt, cmd[i][j], &opt_d, i);
		else if (cmd[i][j] == '-' && cmd[i][j + 1] && cmd[i][j + 1] == '-')
			return (manage_suspend_opt(i, cmd, opt));
		else if (cmd[i][j] != '-' && !is_number(cmd[i][j]))
		{
			tmp[0] = cmd[i][j];
			tmp[1] = '\0';
			return (ft_error("history", "invalid option", tmp));
		}
		if (opt_d)
		{
			if (cmd[i + 2])
				++i;
		}
	}
	return (1);
}

int			get_hist_options(int i, char **cmd, t_opt_hist *opt)
{
	int		j;
	int		len;

	len = (int)ft_tablen(cmd);
	while (i < len && cmd[i])
	{
		j = -1;
		if (get_opt_in_one_arg(i, cmd, opt) == -1)
			return (-1);
		++i;
	}
//	printf("a:%d\nc: %d\nd:%d\nh:%d\nw:%d\nr:%d\np:%d\n", opt->a, opt->c, opt->d, opt->h, opt->w, opt->r, opt->p);
	return (manage_opt_hist_priority(opt));
}
