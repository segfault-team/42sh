#include "shell.h"

static int	is_only_numbers_before(char *s, int i)
{
	while (--i && s[i] && s[i] != ' ')
		if (!is_number(s[i]))
			return (0);
	return (1);
}

static int	start_by_nb(char *s, int i, int c)
{
	while (s[--i] && s[i] == c)
		;
	if (is_number(s[i]))
		return (1);
	return (0);
}

void		check_parsing_double(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] && is_number(e->line[*i - 1])
		&& is_only_numbers_before(e->line, *i)
		&& e->line[*i + 1] && e->line[*i + 1] != '&')
	{
		if (e->line[*i + 1] == ' ')
			e->line[++*i] = '&';
		else if (e->line[*i + 1] != e->line[*i])
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
		e->line[*i + 1] != c && e->line[*i + 1] != ' '
		&& !start_by_nb(e->line, *i, e->line[*i]))
		insert_char(e, ' ', ++(*i));
}

void		check_parsing_simple(t_env *e, int *i, char c)
{
	if (*i && e->line[*i - 1] != ' '
		&& e->line[*i - 1] != '\\' && e->line[*i - 1] != c)
		insert_char(e, ' ', (*i)++);
	if (*i && e->line[*i + 1] && e->line[*i + 1] != ' ')
		insert_char(e, ' ', ++(*i));
}
