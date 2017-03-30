#include "shell.h"

static char		*ft_find_exec_readdir(char *paths, char *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*exec;

	exec = NULL;
	if ((dir = opendir(paths)) != NULL)
	{
		while ((dirent = readdir(dir)) != NULL)
		{
			if (ft_strequ(dirent->d_name, cmd))
			{
				exec = ft_strdup(dirent->d_name);
				break ;
			}
		}
		if (closedir(dir))
			ft_error("closedir", "failed closing dir", paths);
	}
	return (exec);
}

char			*ft_find_exec(char **paths, char *cmd)
{
	char			*exec;
	char			*path;
	char			*tmp;
	int				i;

	i = -1;
	exec = NULL;
	path = NULL;
	if (!cmd || !cmd[0])
		return (NULL);
	if ((cmd[0] == '.' || cmd[0] == '/'))
	{
		if (ft_isexec(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (paths[++i])
		if ((exec = ft_find_exec_readdir(paths[i], cmd)) != NULL)
		{
			tmp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(tmp, exec);
			strfree(&tmp);
			strfree(&exec);
			break ;
		}
	return (path);
}

char			**ft_find_paths(char **env)
{
	char	*value;
	char	**paths;

	paths = NULL;
	value = NULL;
	if ((value = ft_getenv(env, "PATH")) == NULL)
		paths = ft_strsplit(PATH, ':');
	else
	{
		paths = ft_strsplit(value, ':');
		strfree(&value);
	}
	return (paths);
}

void			ft_close(int fd)
{
	if (fd != 1 && fd != 0)
		if (close(fd) == -1)
			ft_error(SH_NAME, "Close failed on fd", NULL);
}

static int		ft_fork_exec(char *exec, char **cmd, t_env *e)
{
	static int	prev_red_index = -1;
	t_job		*son;
	pid_t		pid;

	if ((pid = fork()) < 0)
		ft_error(SH_NAME, "failed to fork process", NULL);
	if (pid)
	{
		++e->child_running;
		ft_close(FD.fd[1]);
		ft_close(FD.in);
	}
	else
	{
		if (redirection_before_cmd(e) == -1)
			exit(0);
		if ((is_input_in_next_cmd(e, RED_INDEX) || is_input_redir(e, RED_INDEX))
					&& RED_INDEX != prev_red_index)
			if (redir_input(e) == -1 && ft_printf("\n"))
				exit(0);
		ft_redirect(FD.in, STDIN_FILENO);
		execve(exec, &cmd[0], e->env);
	}
	prev_red_index = RED_INDEX;
	// POSSIBLE ERREUR ICI :
	// DH4RM4 add it for this cmd:
	// sort << test >&- > test1
	while (is_aggregator(e, RED_INDEX) || is_heredoc(e, RED_INDEX))
		struct_find_red(e);
	if ((son = ft_new_job(e->jobs, pid)) == NULL)
		return (ft_error(SH_NAME, "malloc failed", NULL));
	e->jobs = son;
	return (0);
}

int				ft_exec(char **cmd, t_env *e)
{
	int		ret;
	char	**paths;
	char	*exec;

	ret = 0;
	exec = NULL;
	paths = ft_find_paths(e->env);
	exec = ft_find_exec(paths, cmd[0]);
	if (!exec || access(exec, F_OK))
	{
		strfree(&exec);
		ft_free_tab(paths);
		paths = NULL;
		return (ft_error(cmd[0], "Command not found", NULL));
	}
	if (access(exec, X_OK | R_OK) == 0 || ft_issticky(exec))
		ret = ft_fork_exec(exec, cmd, e);
	else
		ret = ft_error(exec, "Permission denied", NULL);
	ft_free_tab(paths);
	paths = NULL;
	strfree(&exec);
	return (ret);
}

int				ft_exec_cmd(t_env *e, char **cmd)
{
	int			ret;
	int			stat;
	t_logic		*ptr;

	ret = 0;
	stat = 0;
	e->cmd_len = ft_tablen(cmd);
	tcaps_reset(e);
	if (e->cmd_len)
	{
		e->logix = ft_split_logic(e->logix, cmd);
		if (e->logix == NULL)
			return (ft_error(SH_NAME, "malloc failed.", NULL));
		ptr = e->logix;
		while (ptr)
		{
			if (ptr->op > 0)
				stat = ft_waitlogix(e);
			if (ptr->op < 0 || (ptr->op == AND && !ret && !stat) ||
					(ptr->op == OR && (ret || stat)))
			{
				if (ft_is_builtin(ptr->atom[0]))
					ret = ft_exec_builtin(e, ptr->atom);
				else
					ret = ft_exec(ptr->atom, e);
			}
			ptr = ptr->next;
		}
		ft_freelogic(e->logix);
	}
	e->cmd_len = 0;
	return (ret);
}
