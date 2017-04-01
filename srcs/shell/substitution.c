#include "shell.h"

static void	manage_quote(char *quote, char current)
{
	if (!(*quote))
		*quote = current;
	else if (current == *quote)
		*quote = '\0';
}

static int	is_ret_last_cmd_ret(char *line, int i)
{
	if (!line[i + 1])
		return (0);
	if (line[i] == '$' && line[i + 1] == '?' &&
		(line[i + 2] == ' ' || !line[i + 2]))
		return (1);
	return (0);
}

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
	char	quote;
	int		ret;
	char	*user_dir;

	i = -1;
	ret = 0;
	quote = '\0';
	user_dir = ft_strdup("/Users/");
	while (e->cat[y][z][++i])
	{
		if (ret == -1)
		{
			strfree(&user_dir);
			return (-1);
		}
		if ((e->cat[y][z][i] == '"' || e->cat[y][z][i] == '\'') && i - 1 >= 0 &&
			e->cat[y][z][i - 1] != '\\')
			manage_quote(&quote, e->cat[y][z][i]);
		else if (e->cat[y][z][i] == '~' && !i && e->cat[y][z][i + 1]
				&& e->cat[y][z][i + 1] != ' '
				&& e->cat[y][z][i + 1] != '/')
			do_substitution(&e->cat[y][z], &i, user_dir, 0);
		else if (e->cat[y][z][i] == '~' && !quote && !i)
			do_substitution(&e->cat[y][z], &i, e->home, 0);
		else if (e->cat[y][z][i] == '!' && !quote)
			ret = manage_exclamation_mark(e, &i, y, z);
		else if (e->cat[y][z][i] == '$' && e->cat[y][z][i + 1])
			ret = do_env_subs(e, &e->cat[y][z], &i);
		else if (is_ret_last_cmd_ret(e->cat[y][z], i))
			do_substitution(&e->cat[y][z], &i, e->last_ret, 2);
	}
	strfree(&user_dir);
	if (ret)
		ft_printf("%s\n", e->cat[y][z]);
	return (ret);
}
