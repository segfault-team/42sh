#include "libft.h"
#include "jc.h"

t_process	ft_new_process(void)
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

t_job		ft_new_job(void)
{
	t_job	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = NULL;
	new->command = NULL;
	new->first_process = NULL;
	new->pgid = 0;
	new->notified = 0;
	new->tmodes = 0;
	new->stdin = -1;
	new->stdout = -1;
	new->stderr = -1;
	return (new);
}

int			main(int ac, char **av)
{
	char	*line;
	t_job	*first_job;
	t_job	*ptr;

	if (ac == 2)
	{
		while (get_next_line(STDIN_FILENO, &line))
		{
			
		}
	}
	return (0);
}
