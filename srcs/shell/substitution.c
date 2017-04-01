#include "shell.h"

void		do_substitution(char **target, int *curr_pos, char *substitute,
							int nb_char_to_jump)
{
	char	*new;
	char	*tmp;
	char 	*ret;

	new = ft_strnew((int)(ft_strlen(*target) + (int)ft_strlen(substitute)));
	ret = new;
	tmp = *target;
	while (*target && **target)
	{
		if (*target == &tmp[*curr_pos] && substitute)
			ft_replace_word(&new, substitute, &*target, nb_char_to_jump + 1 );
		else
		{
			*new = **target;
			new++;
		}
		*target = *target + 1;
	}
	strfree(&tmp);
	*target = ret;
}

int			substitution(t_env *e, int y, int z)
{
	int		i;
	int		ret;
	char	*user_dir;
	char	*tmp;

	i = -1;
	ret = 0;
	user_dir = ft_strdup("/Users/");
	while (e->cat[y][z][++i])
	{
		if (ret == -1)
		{
			strfree(&user_dir);
			return (-1);
		}
		else if (e->cat[y][z][i] == '~' && !i && e->cat[y][z][i + 1]
				&& e->cat[y][z][i + 1] != ' '
				&& e->cat[y][z][i + 1] != '/')
			do_substitution(&e->cat[y][z], &i, user_dir, 0);
		else if (e->cat[y][z][i] == '~' && !i)
		{
			tmp = ft_getenv(e->env, "HOME");
			if (!tmp)
				tmp = ft_strdup(e->home);
			do_substitution(&e->cat[y][z], &i, tmp, 0);
			ft_strdel(&tmp);
		}
		else if (e->cat[y][z][i] == '$' && e->cat[y][z][i + 1])
			ret = do_env_subs(e, &e->cat[y][z], &i);
	}
	strfree(&user_dir);
	return (ret);
}
