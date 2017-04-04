#include "shell.h"

static int		ft_check_line(t_env *e)
{
	char *tmp;

	if (!e->line && !MULTI)
		return (0);
	else if (!e->line)
		e->line = ft_strdup("\n");
	else if (is_bad_line(e->line))
		return (0);
	if (check_quote(e->line))
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
	tcaps_ctrl_end(e);
	ft_putchar('\n');
	ft_prompt(e->prompt);
	return (0);
}

int				ft_multiline(t_env *e)
{
	char	*tmp;
	int		check;

	check = 0;
	tmp = NULL;
	if ((check = ft_check_line(e)) == 0 && !MULTI)
		return (1);
	if (check_last_char(e, '\\') || check_last_char(e, '|') || check == 42)
	{
		ft_printf("hereb %d\n", check);
		return (manage_multi(e, tmp, check));
	}
	else if (MULTI)
	{
		tmp = ft_strjoin(MULTI, e->line);
		strfree(&e->line);
		e->line = tmp;
		strfree(&MULTI);
		if (!e->hdoc_words)
		{
			strfree(&e->prompt);
			e->prompt = ft_strdup(STD_PROMPT);
		}
	}
	return (1);
}
