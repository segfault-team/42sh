#include "shell.h"

int			ft_unsetenv(char ***env, char *name)
{
	size_t	pos;
	char	*nameequ;
	char	**ptr;
	char	**tmp;

	pos = -1;
	ptr = *env;
	nameequ = ft_strjoin(name, "=");
	if (ptr && name)
	{
		while (ptr[++pos])
		{
			if (ft_strnequ(ptr[pos], nameequ, ft_strlen(nameequ)))
			{
				tmp = ft_tabpop(ptr, pos);
				ft_free_tab(*env);
				*env = tmp;
				strfree(&nameequ);
				return (1);
			}
		}
	}
	strfree(&nameequ);
	return (-1);
}

int			ft_unsetenv_blt(t_env *e, char **cmd)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_tablen(cmd);
	if (len > 1)
	{
		while (++i < (int)len)
		{
			if (ft_strequ(cmd[i], "all"))
			{
				ft_free_tab(e->env);
				e->env = NULL;
			}
			else if (ft_unsetenv(&e->env, cmd[i]) > 0)
				return (1);
		}
		return (-1);
	}
	return (ft_error("unsetenv", "too few arguments", NULL));
}
