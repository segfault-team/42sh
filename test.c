#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char	**ft_tabnew(size_t size);

int main(int ac, char **av, char **env)
{
	int	fd[2];
	pid_t	pid;
	char	**twc;
	char	buf[4096];

	twc = ft_tabnew(3);
	twc[0] = strdup("wc");
	twc[1] = strdup("-l");
	twc[2] = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/ls", av, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execve("/usr/bin/wc", twc, env);
	}
	return (0);
}
