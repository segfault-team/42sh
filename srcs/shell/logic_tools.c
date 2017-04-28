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
