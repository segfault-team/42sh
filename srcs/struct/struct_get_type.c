#include "shell.h"

void		del_elem_magic(int i, t_env *e)
{
	strfree(&e->magic[i - 1].type);
	if (ft_strcmp("red", e->magic[i - 1].type))
		e->magic[i - 1].type = ft_strdup("ignore");
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
	else if (is_only_numbers(e->magic[i].cmd) ||
			 !ft_strcmp(e->magic[i].cmd, "-"))
		e->magic[i].type = ft_strdup("fd_aggregator");
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
	int	already_output;

	i = -1;
	already_output = 0;
	while (e->magic[++i].cmd)
	{
		if (is_redir_from_symbol(e, i))
			already_output = 0;
		if (already_output)
			e->magic[i].type = ft_strdup("ignore");
		else if (red_strstr(e->magic[i].cmd))
			e->magic[i].type = ft_strdup("red");
		else if (struct_check_cmd(i, e))
			e->magic[i].type = ft_strdup("cmd");
		else
			struct_arg_red(i, e);
		if (!ft_strcmp(e->magic[i].type, "output"))
		{
			ft_printf("boid\n");
			already_output = 1;
		}
	}
	magic_realloc(e);
}
