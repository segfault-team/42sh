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
//		for (int j = 0; e->cmd[j] != NULL ; j++)
//			ft_printf("i: %d CMD: %s\n", i, e->cmd[j]);
		if (!check && struct_check_cmd(i, e))
			e->magic[i].type = ft_strdup("cmd");
		else if (red_strstr(e->magic[i].cmd))
		{
			e->magic[i].type = ft_strdup("red");
			ft_remove_tab(e->cmd, i, e->check_remove_tab++);
			++check;
		}
		else if (check)
		{
			ft_remove_tab(e->cmd, i, e->check_remove_tab++);
			struct_arg_red(i, e);
		}
	}
	magic_realloc(e);
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
