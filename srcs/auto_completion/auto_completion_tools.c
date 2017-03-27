#include "shell.h"

int		ft_is_dir(char *target)
{
	struct stat	s;
	int			ret;

	ret = 0;
	if (stat(target, &s) != 1)
		if (S_ISDIR(s.st_mode))
			ret = 1;
	return (ret);
}
