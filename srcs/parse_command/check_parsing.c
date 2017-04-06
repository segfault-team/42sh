#include "shell.h"

static int	is_only_numbers_before(char *s, int i)
{
	while (--i && s[i] && s[i] != ' ')
		if (!is_number(s[i]))
			return (0);
	return (1);
}

void	check_parsing_double(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] && is_number(e->line[*i - 1])
		&& is_only_numbers_before(e->line, *i)
		&& e->line[*i + 1] && e->line[*i + 1] != '&')
	{
		if (e->line[*i + 1] == ' ')
			e->line[++*i] = '&';
		else
			insert_char(e, '&', ++(*i));
		return ;
	}
	else if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i > 1 && e->line[*i - 1] && e->line[*i - 2]
			&& e->line[*i - 1] == c && e->line[*i - 2] == c)
		insert_char(e, ' ', (*i)++);
	if (*i + 1 <= (int)ft_strlen(e->line) - 1 && e->line[*i + 1] &&
		e->line[*i + 1] != c && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}

void	check_parsing_simple(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i && e->line[*i + 1] && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}
