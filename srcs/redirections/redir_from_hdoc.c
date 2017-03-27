#include "shell.h"

int	redir_from_hdoc(t_env *e)
{
	int		i;
	int		len;
	char	**tmp;

	i = -1;
	tmp = (char **)e->hdoc->content;
	if (!tmp[i + 1])
		return (0);
	while (tmp[++i])
	{
		len = (int)ft_strlen(tmp[i]);
		if (tmp[i][len] != '\\')
			ft_putendl_fd(tmp[i], FD.fd[1]);
		else
			ft_putstr_fd(tmp[i], FD.fd[1]);
	}
	ft_close(FD.fd[1]);
	FD.in = FD.fd[0];
	e->hdoc = e->hdoc->next;
	return (1);
}
