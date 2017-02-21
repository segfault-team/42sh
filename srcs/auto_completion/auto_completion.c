#include "shell.h"

static char	*get_path_from_arg(char *arg)
{
	char	*path;
	int		i;

	i = ft_strlen(arg) - 1;
	while ( i > 0 && ft_isalpha(arg[i - 1]))
		--i;
	if (!i || (i > 0 && arg[i - 1] == ' '))
		return ((path = getcwd(NULL, 0)));
	path = ft_strnew(i);
	ft_strncpy(path, arg, i);
	return (path);
}

static char *isolate_arg_to_complete(char *arg)
{
	int     i;
	int     j;
	char    *ret;

	i = ft_strlen(arg) - 1;
	if (!i)
		return (arg);
	j = 0;
	while (i > 0 && ft_isalpha(arg[i - 1]))
		--i;
	if (!(ret = ft_strnew(ft_strlen(arg) - i)))
		return (NULL);
	while (arg[i])
		ret[j++] = arg[i++];
	return (ret);
}

static void	complete_arg(t_env *e, char *arg)
{
	char	**content;
	char	*path;

	path = get_path_from_arg(arg);
	arg = isolate_arg_to_complete(arg);
	content = get_valid_content_from_path(path, arg);
	if (ft_tablen(content) == 1)
		print_auto_completion(e, content[0]);
}

int			auto_completion(t_env *e)
{
	char	**line_split;
	char	*last_arg;

	if (!e->line)
		return (0);
	line_split = ft_strsplit(e->line, ' ');
	if (line_split[1])
	{
		if (NB_MOVE == NB_READ)
			last_arg = ft_strdup(line_split[ft_tablen(line_split) - 1]);
		complete_arg(e, last_arg);
	}
	ft_free_tab(line_split);
	return (1);
}
