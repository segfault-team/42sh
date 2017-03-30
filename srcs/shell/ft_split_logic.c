#include "shell.h"

/*
**	Splits the command based on logical operators.
**	It fills a chained list, which holds the command and
**	the logical operator associated.
**	The first command have a l.op. of -42.
**		ex:   $> true && echo LOL
**		-->		{true, -42} -> {echo LOL, AND}
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
	return (x);
}
