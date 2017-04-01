#include "shell.h"

static void	manage_quote(char *quote, char current)
{
	if (!(*quote))
		*quote = current;
	else if (current == *quote)
		*quote = '\0';
}

static int	is_ret_last_cmd_ret(char *line, int i)
{
	if (!line[i + 1])
		return (0);
	if (line[i] == '$' && line[i + 1] == '?' &&
		(line[i + 2] == ' ' || !line[i + 2]))
		return (1);
	return (0);
}

void		do_substitution(t_env *e, int *curr_pos, char *substitute,
							int nb_char_to_jump)
{
	char	*new;
	int		i_line;
	int		i_new;
	int		i_sub;

	new = ft_strnew((int)(ft_strlen(e->line) + (int)ft_strlen(substitute)));
	i_line = -1;
	i_sub = -1;
	i_new = -1;
	while (e->line[++i_line])
	{
		if (i_line == *curr_pos)
		{
			while (substitute[++i_sub])
			{
				new[++i_new] = substitute[i_sub];
				++(*curr_pos);
			}
			i_line += nb_char_to_jump;
		}
		else
			new[++i_new] = e->line[i_line];
	}
	new[++i_new] = '\0';
	strfree(&e->line);
	e->line = new;
}

int			substitution(t_env *e)
{
	int		i;
	char	quote;
	int		ret;
	char	*user_dir;

	i = -1;
	ret = 0;
	quote = '\0';
	user_dir = ft_strdup("/Users/");
	if (e->line[0] && e->line[0] == '~')
		return (ft_error(SH_NAME, e->home, ": is a directory"));
	while (e->line[++i])
	{
		if (ret == -1)
			return (-1);
		if ((e->line[i] == '"' || e->line[i] == '\'') && i - 1 >= 0 &&
			e->line[i - 1] != '\\')
			manage_quote(&quote, e->line[i]);
		else if (e->line[i] == '~' && i && e->line[i - 1] == ' '
				&& e->line[i + 1] && e->line[i + 1] != ' ')
			do_substitution(e, &i, user_dir, 0);
		else if (e->line[i] == '~' && !quote && i && e->line[i - 1] == ' ')
			do_substitution(e, &i, e->home, 0);
		else if (e->line[i] == '!' && !quote)
			ret = manage_exclamation_mark(e, &i);
		else if (e->line[i] == '$' && e->line[i + 1] && e->line[i + 1] == '(')
			ret = do_env_subs(e, &i);
		else if (is_ret_last_cmd_ret(e->line, i))
			do_substitution(e, &i, e->last_ret, 3);
	}
	strfree(&user_dir);
	if (ret)
	{
		ft_printf("%s\n", e->line);
		ret = 0;
	}
	return (ret);
}
