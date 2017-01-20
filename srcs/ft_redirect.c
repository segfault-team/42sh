#include "shell.h"

void	ft_redirect(char *cmd, t_env *e)
{
  int	i;

  i = -1;
  while (cmd[++i])
    {
      if (i && cmd[i - 1] == '>' && cmd[i] == '>')
	ft_two_sup(&cmd);
      else if (i && cmd[i - 1] == '>' && cmd[i] != '>')
	ft_one_sup(&cmd);
      else if (i && cmd[i - 1] == '<' && cmd[i] == '<')
	ft_two_min(&cmd);
      else if (i && cmd[i - 1] == '<' && cmd[i] != '<')
	ft_one_min(&cmd);
    }
}
