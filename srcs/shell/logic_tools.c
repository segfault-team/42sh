#include "shell.h"

t_logic		*ft_new_logic(void)
{
	t_logic		*x;

	if ((x = malloc(sizeof(*x))) == NULL)
		return (NULL);
	x->atom = NULL;
	x->next = NULL;
	x->op = 0;
	return (x);
}

/*
**	Check for logical operators
*/

int			ft_check_op(char *s)
{
	if (ft_strequ(s, "&&"))
		return (AND);
	if (ft_strequ(s, "||"))
		return (OR);
	return (0);
}

void		ft_freelogic(t_logic *x)
{
	t_logic	*ptr;

	ptr = x;
	while (x)
	{
		ft_tabfree(x->atom);
		ptr = x->next;
		free(x);
		x = ptr;
	}
}

int			ft_waitlogix(t_env *e)
{
	int		status;
	t_job	*ptr;

	if (!e->jobs)
		return (-1);
	ptr = e->jobs;
	waitpid(ptr->pid, &status, WUNTRACED);
	ft_handle_ret_signal(status);
	e->jobs = e->jobs->next;
	free(ptr);
	if (!status)
		return (1);
	return (-1);
}
