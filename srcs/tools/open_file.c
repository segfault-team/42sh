#include "shell.h"

int	open_file(char *file, int flags, mode_t mode)
{
	struct stat	stat;
	int			fd;

	ft_bzero(&stat, sizeof(struct stat));
	if (access(file, F_OK) < 0)
		return (ft_error("no such file: ", file, NULL));
	if (access(file, R_OK) < 0)
		return (ft_error("permission denied: ", file, NULL));
	lstat(file, &stat);
	if (S_ISDIR(stat.st_mode))
		return (ft_error("read failed", file, "is a directory"));
	if ((fd = open(file, flags, mode)) == -1)
		return (ft_error(file, "Resource temporarily unavailable", NULL));
	return (fd);
}
