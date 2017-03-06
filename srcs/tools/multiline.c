#include "shell.h"


static int		ft_isspace(char c)
{
	return ((c == ' ' || c == '\t'));
}
static int 		ft_check_pipe(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	if (e->line[0] == '|')
	{
		/*pareil qu'en dessous*/
		tcaps_ctrl_end(e);
		ft_putstr_fd("\nGERER ERROR", 2);
		return (0);
	}
	while (e->line[++i])
	{
		if (i && e->line[i] == '|')
		{
			j = i + 1;
			while (e->line[j])
			{
				if (e->line[j] == '|')
				{
					/*Ne pas ecrire l'erreur ici, retourner -1 et gerer dans tcaps_enter apres ctrl_end*/
					tcaps_ctrl_end(e);
					ft_putstr_fd("\nGERER ERROR", 2);
					return (0);
				}
				if (!ft_isspace(e->line[j]))
					break;
				j++;
			}
			if (!e->line[j])
				return (1);
		}
	}
	return (0);
}

static int		ft_check_line(t_env *e)
{
	if (!e->line)
		//return (-1);
		return (-1);
	if (ft_check_pipe(e))
		return (0);
//	if (!ft_matchquotes(e->line))
//		return (0);
	return (1);
}

int		ft_multiline(t_env *e)
{
	char 	*tmp;
	int		check;

	if ((check = ft_check_line(e)) < 0)
	{
		strfree(&e->prompt);
		e->prompt = ft_strdup(STD_PROMPT);
		return (1);
	}
	if ((e->line && NB_READ >= 2 && 
				e->line[NB_READ - 1] == '\\' && e->line[NB_READ - 2] != '\\')
			|| !check)
	{
		strfree(&e->prompt);
		e->prompt = ft_strdup(BS_PROMPT);
		tmp = ft_strjoin(MULTI, e->line);
		strfree(&MULTI);
		MULTI = tmp;
		if (check)
			MULTI[ft_strlen(MULTI) - 1] = '\0';
		strfree(&e->line);
		NB_READ = 0;
		NB_MOVE = 0;
		ft_printf("\n%s", e->prompt);
		return (0);
	}
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
