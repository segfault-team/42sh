#include "shell.h"

int	open_file(char *file, int flags, mode_t mode)
{
	int	fd;

	if (access(file, F_OK))
		return (ft_error(SH_NAME, "no such file: ", file));
	if (access(file, R_OK))
		return (ft_error(SH_NAME, "permission denied: ", file));
	if ((fd = open(file, flags, mode)) == -1)
		return (ft_error(SH_NAME, "fail open file: ", file));
	return (fd);
}
