#include "shell.h"

static void	manage_quote(char *quote, char current)
{
	if (!(*quote))
		*quote = current;
	else if (current == *quote)
		*quote = '\0';
}

void		do_substitution(t_env *e, int *curr_pos, char *substitute, int nb_char_to_jump)
{
	char	*new;
	int		i_line;
	int		i_new;
	int		i_sub;

	new = ft_strnew((int)(ft_strlen(e->line) + ft_strlen(substitute)));
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
			--(*curr_pos);
			i_line += nb_char_to_jump;
		}
		else
			new[++i_new] = e->line[i_line];
	}
	new[++i_new] = '\0';
	strfree(&e->line);
	e->line = new;
}

int 		substitution(t_env *e)
{
	int		i;
	char	quote;
	int		ret;

	i = -1;
	ret = 0;
	quote = '\0';
	if (e->line[0] && e->line[0] == '~')
		return (ft_error(SH_NAME, e->home, ": is a directory"));
	while (e->line[++i])
	{
		if (ret == -1)
			return (-1);
		if ((e->line[i] == '"' || e->line[i] == '\'') && i - 1 >= 0 &&
			e->line[i - 1] != '\\')
			manage_quote(&quote, e->line[i]);
		else if (e->line[i] == '~' && !quote && i && e->line[i - 1] == ' ')
			do_substitution(e, &i, e->home, 0);
		else if (e->line[i] == '!' && !quote)
			ret = manage_exclamation_mark(e, &i);
	}
	if (ret)
		ft_printf("%s\n", e->line);
	return (ret);
}


