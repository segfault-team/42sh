#include "shell.h"

int	struct_len(t_magic *magic)
{
	int	len;

	len = 0;
	if (magic)
		while (magic[len].cmd)
			++len;
	return (len);
}

void	magic_type(t_env *e)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (e->magic[++i].cmd)
	{
		if (!check && struct_check_cmd(i, e))
			e->magic[i].type = ft_strdup("cmd");
		else if (red_strstr(e->magic[i].cmd))
		{
			e->magic[i].type = ft_strdup("red");
			++check;
		}
		else if (check)
			struct_arg_red(i, e);
/*		else if (struct_check_input(e->magic[i].cmd))
			e->magic[i].type = ft_strdup("input");
		else if (struct_check_output(e->magic[i].cmd))
			e->magic[i].type = ft_strdup("output");
*/	}
}

// POSSIBLE ERREUR SUR LE DERNIER FREE
// ON AVANCE A L AVEUGLE
// INDIANA JONES
void	magic_free(t_env *e)
{
	int	i;

	i = -1;
	if (e->magic)
	{
		while (e->magic[++i].cmd)
		{
			if (e->magic[i].cmd)
			{
				free(e->magic[i].cmd);
				e->magic[i].cmd = NULL;
			}
			if (e->magic[i].type)
			{
				free(e->magic[i].type);
				e->magic[i].type = NULL;
			}
		}

//		free(e->magic);
	}
}

