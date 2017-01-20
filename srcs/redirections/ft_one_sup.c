#include "shell.h"

static int	ft_ispace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/*
** for access() R_OK | W_OK | X_OK | F_OK = check existence
*/

int		open_valid(t_env *e, char *file, int rights)
{
	if (access(file, F_OK) < 0)
	{
	//	ft_error_msh(P_DENIED, ARGS[1]);
		return (0);
	}
	if (access(file, rights) < 0)
	{
	//	ft_error_msh(P_DENIED, ARGS[1]);
		return (0);
	}
	return (1);
}

void	ft_one_sup(t_env *e, char **cmd)
{
	int		i;
	int		mem;
	int		len;
	char	*file;

	i = 0;
	len = 0;
	while (*cmd[i] != '>')
		++i;
	while (ft_ispace(*cmd[++i]))
		;
	mem = i;
	while (*cmd[++i] && *cmd[i] != '>' && *cmd[i] != ' ')
		++len;
	file = ft_strsub(*cmd, mem, i - mem);
	if (open_valid(e, *cmd, R_OK))
	  if (!(FDOUT = open(file, O_RDWR | O_CREAT | O_TRUNC)))
	    ft_printf(2, "GERER ERRUR");
	free(file);
}
