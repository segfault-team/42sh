#include "shell.h"

int	redir_from_hdoc(t_env *e)
{
	int	i;
	int	len;

	i = -1;
	if (!e->hdoc->content[i + 1])
		return (0);
	while (e->hdoc->content[++i])
	{
		len = (int)ft_strlen(e->hdoc->content[i]);
		if (e->hdoc->content[i][len] != '\\')
			ft_putendl_fd(e->hdoc->content[i], FD.fd[1]);
		else
			ft_putstr_fd(e->hdoc->content[i], FD.fd[1]);
	}
	ft_close(FD.fd[1]);
	FD.in = FD.fd[0];
	e->hdoc = e->hdoc->next;
	return (1);
}
