#include "shell.h"

#define ERROR           -420
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1

typedef struct	s_aggre_elems
{
	int			nb_chevron;
	int			nb_ampersand;
	int			type;
}				t_aggre_elems;

static int		nb_elems_is_invalid(t_aggre_elems *ag)
{
	int error;

	error = 0;
	if (ag->nb_chevron > 1)
		error = dprintf(STDERR_FILENO, "sh: syntax error - too many\
				chevrons in your aggregator\n");
	else if (ag->nb_ampersand > 1)
		error = dprintf(STDERR_FILENO, "sh: syntax error - too many\
				ampersands in your aggregator\n");
	else if (ag->type == ERROR)
		error = dprintf(STDERR_FILENO, "sh: syntax error in your\
				aggregator\n");
	if (error)
		ag->type = ERROR;
	return (error);
}

static int		is_valid_char(char c)
{
	if (is_number(c) || c == '>' || c == '<' || c == '-')
		return (1);
	return (0);
}

static void		assign_nb_elems_in_struct(t_aggre_elems *ag, char c)
{
	if (c == '>' || c == '<')
	{
		if (c == '<')
			ag->type = INPUT_AGGRE;
		else
			ag->type = OUTPUT_AGGRE;
		++ag->nb_chevron;
	}
	else if (c == '&')
		++ag->nb_ampersand;
	else if (!is_valid_char(c))
		ag->type = ERROR;
}

int				find_aggregator_type(t_env *e)
{
	int				i;
	t_aggre_elems	ag;

	i = -1;
	ag.nb_chevron = 0;
	ag.nb_ampersand = 0;
	ag.type = -1;
	while (e->magic[RED_INDEX].cmd[++i] && !nb_elems_is_invalid(&ag))
		assign_nb_elems_in_struct(&ag, e->magic[RED_INDEX].cmd[i]);
	return (ag.type);
}
