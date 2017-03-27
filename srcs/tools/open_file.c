#include "shell.h"

int	open_file(char *file, int flags, mode_t mode)
{
	int	fd;

	if (access(file, F_OK) < 0)
		return (ft_error(SH_NAME, "no such file: ", file));
	if (access(file, R_OK) < 0)
		return (ft_error(SH_NAME, "permission denied: ", file));
	if ((fd = open(file, flags, mode)) == -1)
		return (ft_error(SH_NAME, file, "Resource temporarily unavailable"));
	return (fd);
}
