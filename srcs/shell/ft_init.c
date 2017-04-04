#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static void		ft_init_ter(t_env *e)
{
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
	e->last_ret = ft_strdup("0");
	e->check_input = 0;
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
	e->len_mag = 0;
	e->b_hdoc = NULL;
	e->quote = '\0';
	e->last_cmd = NULL;
	MULTI = NULL;
	e->is_out_close = 0;
	e->is_valid_pipe = 1;
	ft_init_ter(e);
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
	ft_init_bis(e);
	ft_bzero(e->buf, 3);
	e->prompt = ft_strdup(STD_PROMPT);
	ft_set_shlvl(e);
	return (tcaps_init(e));
}
