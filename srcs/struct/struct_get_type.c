#include "shell.h"

static int	isRedirSign(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}

/*
**	CHECK IF A REDIRECTION IS IN 'str'
*/

int			red_strstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (isRedirSign(str[i]))
			return (1);
	return (0);
}

/*
**	CHECK IF CURRENT e->magic[i].cmd IS NOT A REDIRECTION
**	OR A FILE FOR REDIRECTION
*/

int			struct_check_cmd(int i, t_env *e)
{
	if (i > 0 && isRedirPipe(e, i - 1))
		return (1);
	else if (i > 0 && isAggregator(e, i - 1) && !isRedirection(e, i))
		return (1);
//	else if (OPERATOR LOGIQUE) return (1);
	else if (i == 0 && !red_strstr(e->magic[i].cmd))
		return (1);
	return (0);
}

void		del_elem_magic(int i, t_env *e)
{
	strfree(&e->magic[i - 1].type);
	if (ft_strcmp("red", e->magic[i - 1].type))
		e->magic[i - 1].type = ft_strdup("ignore");
}

static int	ft_check_input(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, "<") ||
		!ft_strcmp(e->magic[i].cmd, "<<") ||
		!ft_strcmp("input", e->magic[i].type))
		return (1);
	return (0);
}

static int	ft_check_output(int i, t_env *e)
{
	if (!ft_strcmp(e->magic[i].cmd, ">") ||
		!ft_strcmp(e->magic[i].cmd, ">>") ||
		!ft_strcmp(e->magic[i].cmd, "|") ||
		!ft_strcmp("output", e->magic[i].type))
		return (1);
	return (0);
}

void		struct_arg_red(int i, t_env *e)
{
	if (i > 0 && (!ft_strcmp("|", e->magic[i - 1].cmd) ||
				!ft_strcmp(e->magic[i - 1].type, "cmd")))
		e->magic[i].type = ft_strdup("cmd");
	else if (i > 0 && ft_check_input(i - 1, e))
		e->magic[i].type = ft_strdup("input");
	else if (i > 0 && ft_check_output(i - 1, e))
		e->magic[i].type = ft_strdup("output");
	else if (isOnlyNumbers(e->magic[i].cmd) || !ft_strcmp(e->magic[i].cmd, "-"))
		e->magic[i].type = ft_strdup("fd_aggregator");
	if (i > 0 && (!ft_strcmp(e->magic[i - 1].type, "input") ||
				!ft_strcmp(e->magic[i - 1].type, "output")))
		del_elem_magic(i, e);
}

/*
**     REMPLIT LE TABLEAU DE STRUCTURE MAGIC ET ASSOCIE CHAQUE ELEMENTS
**     DE LA CMD AVEC LE TYPE DE L'ELEM. EX: ls -l > test
**  ls  -> "cmd"
**  -l  -> "cmd"
**  >   -> "red"
**  test    -> "output"
*/

void		magic_type(t_env *e)
{
	int i;

	i = -1;
	while (e->magic[++i].cmd)
	{
		if (red_strstr(e->magic[i].cmd))
			e->magic[i].type = ft_strdup("red");
		else if (struct_check_cmd(i, e))
			e->magic[i].type = ft_strdup("cmd");
		else
			struct_arg_red(i, e);
	}
	magic_realloc(e);
}
