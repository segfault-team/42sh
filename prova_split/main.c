#include "libft.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	char	*line;
	char	**tab;
	int		i = 0;
	int		fd;

	ft_printf("--------------\n");
	while (++i < ac)
	{
		fd = open(av[i], O_RDONLY);
		while (get_next_line(fd, &line))
		{
			ft_printf("line: %s\n", line);
			tab = ft_strsplit_quote_bs(line, ' ');
			ft_puttab(tab);
			ft_free_tab(tab);
			free(line);
			ft_printf("--------------\n");
		}
		close(fd);
	}
	return (0);
}
