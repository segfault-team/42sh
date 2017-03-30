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
	e->last_ret = ft_strdup("0");
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

int				ft_init(t_env *e, char **env)
{
	e->new_term = (struct termios *)malloc(sizeof(struct termios));
	e->old_term = (struct termios *)malloc(sizeof(struct termios));
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
	e->prompt = ft_strdup(STD_PROMPT);
	ft_set_shlvl(e);
	return (tcaps_init(e));
}
