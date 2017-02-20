#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "libft.h"

static int	ft_start_with(char *str, char *comp)
{
	int	i;

	i = -1;
	if (ft_strlen(str) < ft_strlen(comp))
		return (0);
	while (comp[++i])
	{
		if (comp[i] != str[i])
			return (0);
	}
	return (1);
}

char		**get_valid_content_from_path(char *curr_path, char *arg)
{
	char			**content;
	DIR				*dir_id;
	struct dirent	*dir_entry;

	content = NULL;
	if ((dir_id = opendir(curr_path)) == NULL)
		ft_printf("MANAGE ERROR");
	while ((dir_entry = readdir(dir_id)) != NULL)
	{
		if (ft_start_with(dir_entry->d_name, arg))
			content = ft_tabcat(content, dir_entry->d_name);
	}
	if (closedir(dir_id))
		ft_error("closedir", "failed closing dir", curr_path);
	return (content);
}
