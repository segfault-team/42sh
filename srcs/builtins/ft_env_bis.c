#include "shell.h"

int		ft_env_error(char *cmd)
{
	ft_error("env", "illegal option --", cmd);
	ft_error("\nusage", "env [-i name1=val1 ...] [-u name]", NULL);
	return (-1);
}

void	ft_env_bis(t_env *e, char ***env_cpy, char **cmd, int i)
{
	char	**tmp;

	tmp = NULL;
	while (ft_strchr(cmd[i], '='))
	{
		tmp = *env_cpy;
		if ((*env_cpy = ft_tabcat(*env_cpy, cmd[i++])) == NULL)
			break ;
		ft_free_tab(tmp);
	}
	e->env = *env_cpy;
	if (cmd[i])
		i = ft_exec_cmd(e, &cmd[i]);
	else
		ft_puttab(e->env);
}
