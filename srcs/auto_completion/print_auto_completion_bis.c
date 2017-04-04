#include "shell.h"

char	ft_file_type(int mode)
{
	char	c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	return (c);
}

char	*ft_perms(int mode)
{
	char	*rwx[8];
	char	*bits;

	bits = (char *)malloc(12 * sizeof(char *));
	rwx[0] = "---";
	rwx[1] = "--x";
	rwx[2] = "-w-";
	rwx[3] = "-wx";
	rwx[4] = "r--";
	rwx[5] = "r-x";
	rwx[6] = "rw-";
	rwx[7] = "rwx";
	bits[0] = ft_file_type(mode);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXUSR) ? 't' : 'T';
	bits[10] = ' ';
	bits[11] = '\0';
	return (bits);
}

char	*file_with_path(t_env *e, char *str)
{
	int		x;
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(e->prefix, str);
	tmp2 = ft_strjoin(e->path, tmp);
	ft_strdel(&tmp);
	x = 0;
	i = ft_strlen(tmp2);
	while (tmp2 && tmp2[x])
	{
		if (tmp2[x] == '\\')
			ft_strncpy(&tmp2[x], &tmp2[x + 1], i - x);
		x++;
	}
	return (tmp2);
}

char	*ft_comp_and_perm(t_env *e, char *str)
{
	struct stat	s;
	char		*tmp;
	char		*fraiche;

	tmp = file_with_path(e, str);
	fraiche = NULL;
	if (lstat(tmp, &s) == -1)
		fraiche = ft_strdup(C_RESET);
	if (!fraiche)
		fraiche = ft_perms(s.st_mode);
	ft_strdel(&tmp);
	return (fraiche);
}

void	ft_fill_files(char **argv, t_env *e)
{
	int				i;
	char			*tmp;

	i = 0;
	while (argv[i])
	{
		e->files[i] = (t_file *)malloc(sizeof(t_file));
		e->files[i]->name = ft_strdup(argv[i]);
		if (e->total_len < ft_strlen(argv[i]))
		{
			e->total_len = ft_strlen(argv[i]);
			e->total_len = e->total_len < e->tcaps.ws.ws_col ?
				e->total_len : e->tcaps.ws.ws_col - 3;
		}
		tmp = ft_comp_and_perm(e, argv[i]);
		e->files[i]->color = ft_pick_color(tmp);
		ft_strdel(&tmp);
		i++;
	}
	e->c_match = i;
	e->files[i] = NULL;
}
