#include "shell.h"

static size_t	ft_arglen(char **cmd, size_t len, int i)
{
	size_t	arglen;

	arglen = (size_t)i;
	while (++arglen < len && ft_strchr(cmd[arglen], '='))
		;
	return (arglen);
}

static int		ft_arg_isdouble(char **args, char *arg, int i)
{
	char	*eval;
	char	**tmp;

	tmp = ft_strsplit(arg, '=');
	eval = ft_strjoin(tmp[0], "=");
	ft_free_tab(tmp);
	while (args[++i])
		if (ft_strnequ(args[i], eval, ft_strlen(eval)))
		{
			strfree(&eval);
			return (1);
		}
	strfree(&eval);
	return (0);
}

static int		ft_opt_i(char **cmd, char ***env_cpy, int i, size_t len)
{
	char	**ptr;
	size_t	arglen;
	int		j;

	arglen = ft_arglen(cmd, len, i);
	ft_free_tab(*env_cpy);
	*env_cpy = ft_tabnew(len + 1);
	ptr = *env_cpy;
	j = 0;
	while (++i < (int)arglen)
	{
		if (cmd[i][0] == '=')
			return (ft_error("env", "invalid argument", cmd[i]));
		if (!ft_arg_isdouble(cmd, cmd[i], i))
		{
			ptr[j] = ft_strdup(cmd[i]);
			++j;
		}
	}
	if (arglen == len)
	{
		ft_puttab(*env_cpy);
		return (0);
	}
	return (i);
}

static int		ft_env_opt(char ***env_cpy, size_t len, char **cmd)
{
	int		i;

	i = 0;
	while (++i < (int)len && cmd[i] && cmd[i][0] == '-' && \
			!ft_strchr(cmd[i], '='))
	{
		if (cmd[i][1] == 'u')
		{
			if (cmd[i + 1] && !cmd[i][2])
				ft_unsetenv(env_cpy, cmd[++i]);
			else
				return (++i);
		}
		else if (cmd[i][1] == 'i')
			return (ft_opt_i(cmd, env_cpy, i, len));
		else
			return (ft_env_error(&cmd[i][1]));
	}
	if (i == (int)len)
	{
		ft_puttab(*env_cpy);
		return (0);
	}
	return (i);
}

int				ft_env(t_env *e, char **cmd)
{
	char	**env_cpy;
	char	**tmp;
	size_t	len;
	int		i;

	i = 1;
	env_cpy = ft_tabdup(e->env);
	tmp = e->env;
//	e->env = env_cpy;
	if ((len = ft_tablen(cmd)) > 1)
	{
		if ((i = ft_env_opt(&env_cpy, len, cmd)) > 0)
			ft_env_bis(e, &env_cpy, cmd, i);
	}
	else
		ft_puttab(e->env);
	ft_free_tab(env_cpy);
	//ft_free_tab(e->env);
	e->env = tmp;
	if (!i)
		return (1);
	return (i);
}
