#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
	int fd[2];
	int copyOut = dup(STDOUT_FILENO);
	int copyErr = dup(STDERR_FILENO);
	int i = -1;
	pid_t pid;
	int in;

	char *cat[3][3];
	cat[0][0] = "/bin/ls";
	cat[0][1] = "-K";
	cat[0][2] = NULL;
	cat[1][0] = "/usr/bin/sort";
	cat[1][1] = "-r";
	cat[1][2] = NULL;
	cat[2][0] = "/usr/bin/wc";
	cat[2][1] = "-l";
	cat[2][2] = NULL;
	cat[3][0] = NULL;
	in = STDIN_FILENO;

	while (cat[++i][0] != NULL)
	{
		pipe(fd);

		pid = fork();
		if (!pid)
		{
			close(fd[0]);
			if (cat[i + 1][0] != NULL)
			{
				dup2(fd[1], STDERR_FILENO);
				dup2(fd[1], STDOUT_FILENO);
			}
			if (in != STDIN_FILENO)
				dup2(in, STDIN_FILENO);
			close(fd[1]);
			execve(cat[i][0], cat[i], env);
		}
		else
		{
			close(fd[1]);
			close(in);
		}
		in = fd[0];
		dup2(copyOut, STDOUT_FILENO);
		dup2(copyErr, STDERR_FILENO);
	}

	char str[4096];
	int ret = read(fd[0], &str, 4096);
	str[ret] = '\0';
	printf("final output:\n%s\n", str);
	return (0);
}
