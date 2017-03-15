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

void		ft_print_logic(t_logic *x)
{
	t_logic	*ptr;

	ptr = x;
	while(ptr)
	{
		ft_printf("-----\n");
		ft_printf("op: %d\n", ptr->op);
		ft_puttab(ptr->atom);
		ft_printf("-----\n");
		ptr = ptr->next;
	}
}

int			ft_waitlogix(t_env *e)
{
	int		status;
	t_job	*ptr;

	if (!e->jobs)
		return (0);
	ptr = e->jobs;
	waitpid(ptr->pid, &status, WUNTRACED);
	ft_handle_ret_signal(status);
	e->jobs = e->jobs->next;
	free(ptr);
	return (status);
}

/*
**
**	Splits the command based on logical operators.
**	It fills a chained list, which holds the command and 
**	the logical operator associated.
**	The first command have a l.op. of -42.
**		ex:   $> true && echo LOL
**		-->		{true, -42} -> {echo LOL, AND}
**
*/

t_logic		*ft_split_logic(t_logic *x, char **cmd)
{
	t_logic		*ptr;
	char		**tmp;
	int			i;
	int			op;
	int			ret;

	if ((x = ft_new_logic()) == NULL)
		return (NULL);
	ptr = x;
	i = -1;
	op = 0;
	x->atom = ft_tabcat(NULL, cmd[++i]);
	x->op = -42;
	while (cmd[++i])
	{
		if ((ret = ft_check_op(cmd[i])))
			op = ret;
		else
		{
			if (op)
			{
				ptr->next = ft_new_logic();
				ptr = ptr->next;
				ptr->op = op;
				op = 0;
			}
			if ((tmp = ft_tabcat(ptr->atom, cmd[i])) == NULL)
			{
				ft_freelogic(x);
				return (NULL);
			}
			ft_tabfree(ptr->atom);
			ptr->atom = tmp;
		}
	}
//	ft_print_logic(x);
	return (x);
}
