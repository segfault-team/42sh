#include "shell.h"

int		is_dir(char *str)
{
	struct stat		info;

	ft_bzero(&info, sizeof(struct stat));
	if (!str || lstat(str, &info) < 0)
		return (-1);
	return (S_ISDIR(info.st_mode));
}
