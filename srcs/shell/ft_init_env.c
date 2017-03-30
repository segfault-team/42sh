#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int		ft_set_home(t_env *e)
{
	int				uid;
	struct passwd	*pwd;

	e->home = NULL;
	if ((e->home = ft_getenv(e->env, "HOME")))
		return (1);
	if ((uid = getuid()))
	{
		if ((pwd = getpwuid(uid)))
		{
			if (pwd->pw_dir)
			{
				e->home = ft_strdup(pwd->pw_dir);
				ft_setenv(&e->env, "HOME", pwd->pw_dir);
				return (1);
			}
		}
	}
	return (0);
}

void		ft_set_shlvl(t_env *e)
{
	char	*lvl;
	int		tmp;

	if ((lvl = ft_getenv(e->env, "SHLVL")))
	{
		tmp = ft_atoi(lvl) + 1;
		free(lvl);
		lvl = ft_itoa(tmp);
		ft_setenv(&e->env, "SHLVL", lvl);
		free(lvl);
	}
	else
		ft_setenv(&e->env, "SHLVL", "1");
}
