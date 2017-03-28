#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static int		ft_set_home(t_env *e)
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

static void		ft_set_shlvl(t_env *e)
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

static void		init_split_delim(t_env *e)
{
	SPLIT_DELIM[0] = ft_strdup("1>&2");
	SPLIT_DELIM[1] = ft_strdup("2>&1");
	SPLIT_DELIM[2] = ft_strdup(">&2");
	SPLIT_DELIM[3] = ft_strdup("&&");
	SPLIT_DELIM[4] = ft_strdup("&>");
	SPLIT_DELIM[5] = ft_strdup("||");
	SPLIT_DELIM[6] = ft_strdup(">&");
	SPLIT_DELIM[7] = ft_strdup(">>");
	SPLIT_DELIM[8] = ft_strdup("<<");
	SPLIT_DELIM[9] = ft_strdup(">");
	SPLIT_DELIM[10] = ft_strdup("<");
	SPLIT_DELIM[11] = ft_strdup("|");
	SPLIT_DELIM[12] = NULL;
}

static void		ft_init_bis(t_env *e)
{
	e->x = 1;
	e->exit = 0;
	e->line = NULL;
	e->line_bkp = NULL;
	e->jobs = NULL;
	e->cmd = NULL;
	e->cut = NULL;
	e->cat = NULL;
	e->child_running = 0;
	e->check_ctrl_c = 0;
	e->i_mag = 0;
	e->magic = NULL;
	e->logix = NULL;
	e->selected = -42;
	e->files = NULL;
	e->path = NULL;
	e->prefix = NULL;
	e->total_len = 0;
	e->start = 0;
	e->heredoc = NULL;
	e->herestop = 0;
	e->herestock = NULL;
	e->hdoc_words = NULL;
	e->hdoc_nb = 0;
	e->hdoc = NULL;
	e->b_hdoc = NULL;
	init_split_delim(e);
	e->last_ret = ft_strdup("0");;
}

char			*init_hist_file(t_env *e)
{
	char	*path;
	char	*ret;

	path = NULL;
	if (!e->home || (int)ft_strlen(e->home) == 0)
	{
		path = getcwd(NULL, 0);
		ret = ft_strjoin(path, HIST_NAME);
	}
	else
		ret = ft_strjoin(e->home, HIST_NAME);
	return (ret);
}

void			ft_init(t_env *e, char **env)
{
	e->history = NULL;
	e->trunc_in_history = 0;
	e->env = ft_tabdup(env);
	e->last_cmd = NULL;
	e->quote = '\0';
	if (!ft_set_home(e))
		ft_error(SH_NAME, "WARNING: no home set", NULL);
	e->hist_file = init_hist_file(e);
	if (ft_read_history(e) < 0)
	{
		ft_free_tab(e->history);
		e->history = NULL;
	}
	FD.stdin = dup(STDIN_FILENO);
	FD.stdout = dup(STDOUT_FILENO);
	FD.stderr = dup(STDERR_FILENO);
	MULTI = NULL;
	ft_init_bis(e);
	ft_bzero(e->buf, 3);
	e->prompt = ft_strdup("$> ");
	ft_set_shlvl(e);
	tcaps_init(e);
}
