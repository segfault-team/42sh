#include "shell.h"

void	check_parsing_double(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i > 1 && e->line[*i - 1] && e->line[*i - 2]
			 && e->line[*i - 1] == c && e->line[*i - 2] == c)
		insert_char(e, ' ', (*i)++);
}

void	check_parsing_simple(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i && e->line[*i + 1] && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}
