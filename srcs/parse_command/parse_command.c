#include "shell.h"

static void	manage_chev(t_env *e, int *i)
{
	if (*i + 1 < (int)ft_strlen(e->line))
		if (e->line[*i + 1] && e->line[*i + 1] != '&')
			check_parsing_double(e, i, e->line[*i]);
}
// SUPPRIMER SPLIT DELIM

void	parse_command(t_env *e)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	while (e->line[++i])
	{
		if (((e->line[i] == '"') &&
			 ((i - 1 >= 0 && e->line[i - 1] != '\\') || !i)) || e->line[i] == '\'')
		{
			if (!quote)
				quote = e->line[i];
			else if (quote == e->line[i])
				quote = '\0';
		}
		else if (!quote && e->line[i] == '|')
			check_parsing_double(e, &i, e->line[i]);
		else if (!quote && e->line[i] == '&')
			check_parsing_ampersand(e, &i);
		else if (!quote && e->line[i] == ';')
			check_parsing_simple(e, &i, e->line[i]);
		else if (!quote && e->line[i] == '>')
			manage_chev(e, &i);
		else if (!quote && e->line[i] == '<')
			check_parsing_double(e, &i, e->line[i]);
	}
}
