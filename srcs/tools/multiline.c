#include "shell.h"

static int		ft_isspace(char c)
{
	return ((c == ' ' || c == '\t'));
}

static int		is_quote(t_env *e)
{
	int			i;
//	int			bs;

	i = -1;
	while (e->line[++i])
	{
//		e->quote = ft_check_quote_bs(e->line[i], e->quote, bs);
		if (((e->line[i] == '"') &&
			((i - 1 >= 0 && e->line[i - 1] != '\\') || !i)) || e->line[i] == '\'')
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

static int		ft_check_line(t_env *e)
{
	char *tmp;

	if (!e->line && !MULTI)
		return (0);
	else if (!e->line)
		e->line = ft_strdup("\n");
	if (is_quote(e))
	{
		if (ft_strcmp(e->line, "\n"))
		{
			tmp = e->line;
			e->line = ft_strjoin(e->line, "\n");
			ft_strdel(&tmp);
		}
		return (42);
	}
	return (1);
}

static int		manage_multi(t_env *e, char *tmp, int check)
{
	strfree(&e->prompt);
	e->prompt = ft_strdup(BS_PROMPT);
	tmp = ft_strjoin(MULTI, e->line);
	strfree(&MULTI);
	MULTI = tmp;
	if (check && MULTI && MULTI[ft_strlen(MULTI) - 1] == '\\')
		MULTI[ft_strlen(MULTI) - 1] = '\0';
	strfree(&e->line);
	NB_READ = 0;
	NB_MOVE = 0;
	ft_printf("\n%s", e->prompt);
	return (0);
}

int				ft_multiline(t_env *e)
{
	char	*tmp;
	int		check;

	if ((check = ft_check_line(e)) == 0 && !MULTI)
	{
		strfree(&e->prompt);
		e->prompt = ft_strdup(STD_PROMPT);
		return (1);
	}
	if ((e->line && NB_READ >= 2
				&& (check_last_char(e, '\\') || check_last_char(e, '|')))
				|| check == 42)
		return (manage_multi(e, tmp, check));
	else if (MULTI)
	{
		tmp = ft_strjoin(MULTI, e->line);
		strfree(&e->line);
		e->line = tmp;
		strfree(&e->prompt);
		e->prompt = ft_strdup(STD_PROMPT);
	}
	return (1);
}
