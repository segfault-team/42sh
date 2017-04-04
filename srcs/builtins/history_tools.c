#include "shell.h"

static int	is_not_valid_arg(char c)
{
	return (c != 'a' && c != 'c' && c != 'd' && c != 'h'
			&& c != 'r' && c != 'w');
}

static char	*join_char(char c1, char c2)
{
	char	*ret;

	ret = ft_strnew(2);
	ret[0] = c1;
	ret[1] = c2;
	return (ret);
}

static int	output_history_arg_error(char *sh_name, char *error)
{
	ft_printfd(2, "%s: history: %s: invalid option\n", sh_name, error);
	print_history_help();
	return (-1);
}

static int	history_arg_error(char *sh_name, char error)
{
	char	*tmp;

	tmp = join_char('-', error);
	output_history_arg_error(sh_name, tmp);
	strfree(&tmp);
	return (-1);
}

int			is_valid_arg(char **cmd, char *sh_name)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (cmd[1] && cmd[2] && is_only_numbers(cmd[1]))
		return (history_error_with_id(cmd, sh_name, 1));
	while (cmd[++i])
	{
		if (cmd[i][0] == '-')
		{
			j = 0;
			while (cmd[i][++j])
				if (is_not_valid_arg(cmd[i][j]))
					return (history_arg_error(sh_name, cmd[i][j]));
		}
		if (cmd[i][0] != '-' && !is_only_numbers(cmd[i]))
			return (output_history_arg_error(sh_name, cmd[i]));
	}
	return (1);
}
