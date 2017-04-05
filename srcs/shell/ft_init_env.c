#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int			ft_set_home(t_env *e, char *path)
{
	int				uid;
	char			*tmp;
	char			*login;
	struct passwd	*pwd;

	e->home = NULL;
	if ((e->home = ft_getenv(e->env, "HOME")))
		return (1);
	if ((uid = getuid()))
	{
		if ((path = ft_getpath_uid(uid, NULL)))
		{
			e->home = ft_strdup(path);
			ft_setenv(&e->env, "HOME", path);
			return (1);
		}
		if ((login = getlogin()))
		{
			tmp = ft_strjoin(USERS_DIR, login);
			e->home = ft_strdup(tmp);
			ft_setenv(&e->env, "HOME", tmp);
			strfree(&tmp);
			return (1);
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
