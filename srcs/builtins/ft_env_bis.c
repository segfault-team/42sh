#include "shell.h"

int		ft_print_env(char **env_cpy)
{
	ft_puttab(env_cpy);
	return (0);
}

int		ft_env_opt_u_error(void)
{
	ft_printfd(2, "env: option requires an argument -- u\n");
	ft_printfd(2, "usage: env [-i] [-u name]\n");
	ft_printfd(2, "           [name=value] [utility [argument ...]]\n");
	return (-1);
}

int		ft_env_error(char *cmd)
{
	ft_error("env", "illegal option --", cmd);
	ft_printfd(2, "usage: env [-i name1=val1 ...] [-u name]\n");
	return (-1);
}

int		ft_env_opt_u(char ***env_cpy, char **cmd, int i)
{
	if (!cmd || (!cmd[i + 1] && !cmd[i][2]))
		return (ft_env_opt_u_error());
	if (cmd[i + 1])
	{
		if (cmd[++i][0] == '=')
		{
			ft_printfd(2, "env: unsetenv %s: invalid argument", cmd[i]);
			return (-1);
		}
		if (ft_unsetenv(env_cpy, cmd[i]) > 0)
			return (1);
	}
	return (0);
}

void	ft_env_bis(t_env *e, char ***env_cpy, char **cmd, int i)
{
	char	**tmp;

	tmp = NULL;
	while (ft_strchr(cmd[i], '='))
	{
		tmp = *env_cpy;
		if (!(*env_cpy = ft_tabcat(*env_cpy, cmd[i++])))
			break ;
		ft_free_tab(tmp);
	}
	e->env = *env_cpy;
	if (cmd[i])
	{
		e->env_exec = 1;
		i = ft_exec_cmd(e, &cmd[i]);
	}
	else
		ft_puttab(e->env);
}
