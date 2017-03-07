#include "libft.h"
#include "jc.h"
#include <unistd.h>
#include <fcntl.h>

t_process	*ft_new_process(void)
{
	t_process	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = NULL;
	new->argv = NULL;
	new->pid = 0;
	new->completed = 0;
	new->stopped = 0;
	new->status = 0;
	return (new);
}

t_job		*ft_new_job(void)
{
	t_job	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = NULL;
	new->command = NULL;
	new->first_process = NULL;
	new->pgid = 0;
	new->notified = 0;
//	new->tmodes = 0;
	new->stdin = -1;
	new->stdout = -1;
	new->stderr = -1;
	return (new);
}

void		ft_print_jobs(t_job *jb)
{
	t_job	*ptr;

	ptr = jb;
	while (ptr)
	{
		ft_printf("-> %s\n", ptr->command);
		ptr = ptr->next;
	}
}

int			main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_job	*first_job;
	t_job	*ptr;

	if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
			return (-1);
		while (get_next_line(fd, &line))
		{
			ft_printf("____________________________________\n");
			ft_printf("||LINE:		#%s#			||\n", line);
			first_job = ft_split_jobs(line, ';');
			ft_print_jobs(first_job);
			free(line);
			ft_printf("_____________________________________\n");
		}
		close(fd);
	}
	return (0);
}
