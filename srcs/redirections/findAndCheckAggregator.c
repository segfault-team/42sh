#include "shell.h"

#define ERROR           -420
#define INPUT_AGGRE     0
#define OUTPUT_AGGRE    1

typedef struct  s_aggreElems
{
	int nbChevron;
	int nbAmpersand;
	int type;
}               t_aggreElems;

static int nbElemsIsInvalid(t_aggreElems *ag)
{
	int error;

	error = 0;
	if (ag->nbChevron > 1 || ag->nbAmpersand > 1 || ag->type == ERROR)
		error = ft_error(SH_NAME, "syntax error in your aggregator", NULL);
	if (error)
		ag->type = ERROR;
	return (error);
}

static int	isValidChar(char c)
{
	if (isNumber(c) || c == '>' || c == '<' || c == '-')
		return (1);
	return (0);
}

static void	assignNbElemsInStruct(t_aggreElems *ag, char c)
{
	if (c == '>' || c == '<')
	{
		if (c == '<')
			ag->type = INPUT_AGGRE;
		else
			ag->type = OUTPUT_AGGRE;
		++ag->nbChevron;
	}
	else if (c == '&')
		++ag->nbAmpersand;
	else if (!isValidChar(c))
		ag->type = ERROR;

}

int  		findAggregatorType(t_env *e)
{
	int             i;
	t_aggreElems    ag;

	i = -1;
	ag.nbChevron = 0;
	ag.nbAmpersand = 0;
	ag.type = -1;
	while (e->magic[RED_INDEX].cmd[++i] && !nbElemsIsInvalid(&ag))
		assignNbElemsInStruct(&ag, e->magic[RED_INDEX].cmd[i]);
	return (ag.type);
}
