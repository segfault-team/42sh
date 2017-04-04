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

int			ft_freelogic(t_logic *x)
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
	return (-1);
}

int			ft_waitlogix(t_env *e)
{
	int		status;
	t_job	*tmp;

	if (!e->jobs)
	{
		reset_last_ret(e, 127);
		return (-1);
	}
	waitpid(e->jobs->pid, &status, WUNTRACED);
	ft_handle_ret_signal(status);
	tmp = e->jobs;
	e->jobs = e->jobs->next;
	free(tmp);
	reset_last_ret(e, WEXITSTATUS(status));
	if (!status)
		return (1);
	return (-1);
}
