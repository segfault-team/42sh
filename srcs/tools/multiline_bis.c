#include "shell.h"

int		ft_isspace(char c)
{
	return ((c && (c == ' ' || c == '\t')));
}

int		is_quote(t_env *e)
{
	int			i;

	i = -1;
	while (e->line[++i])
	{
		if ((!i || (e->line[i - 1] != '\\' && e->quote != '\''))
			&& ((e->line[i] == '"') || e->line[i] == '\''))
		{
			if (!e->quote)
				e->quote = e->line[i];
			else if (e->quote == e->line[i])
				e->quote = '\0';
		}
	}
	if (e->quote)
		return (1);
	return (0);
}

int		is_bad_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && line[i] != ' ')
		if (line[i] == '|' ||
			line[i] == '&' ||
			line[i] == ';')
			return (1);
	return (0);
}
