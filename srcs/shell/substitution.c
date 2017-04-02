#include "shell.h"

void		do_substitution(char **target, int *curr_pos, char *substitute,
							int nb_char_to_jump)
{
	char	*new;
	char	*tmp;
	char	*ret;

	new = ft_strnew((int)(ft_strlen(*target) + (int)ft_strlen(substitute)));
	ret = new;
	tmp = *target;
	while (*target && **target)
	{
		if (*target == &tmp[*curr_pos] && substitute)
			ft_replace_word(&new, substitute, &*target, nb_char_to_jump + 1);
		else
		{
			*new = **target;
			new++;
		}
		*target = *target + 1;
	}
	strfree(&tmp);
	tmp = ft_strtrim(ret);
	if (tmp)
		*target = escape_specials(tmp, *curr_pos, ft_strlen(substitute));
	else
		*target = tmp;
	ft_strdel(&ret);
	ft_strdel(&tmp);
}

int			substitution(t_env *e, char **str)
{
	int		i;
	int		ret;
	char	*user_dir;
	char	*tmp;

	i = -1;
	ret = 0;
	user_dir = ft_strdup("/Users/");
	while ((*str)[++i])
	{
		if (ret == -1)
		{
			strfree(&user_dir);
			return (-1);
		}
		else if ((*str)[i] == '~'
				&& (*str)[i + 1]
				&& (*str)[i + 1] != ' '
				&& (*str)[i + 1] != '/'
				&& (*str)[i + 1] != '~'
				&& !(*str)[i - 1])
			do_substitution(str, &i, user_dir, 0);
		else if ((*str)[i] == '~'
				&& (!(*str)[i - 1]
				|| (*str)[i - 1] != '~')
				&& (!(*str)[i + 1]
				|| ((*str)[i + 1] != '~'
				&& (*str)[i + 1] != '\''
				&& (*str)[i + 1] != '\"')))
		{
			tmp = ft_getenv(e->env, "HOME");
			if (!tmp)
				tmp = ft_strdup(e->home);
			do_substitution(str, &i, tmp, 0);
			ft_strdel(&tmp);
		}
		else if ((*str)[i] == '$' && (*str)[i + 1])
			ret = do_env_subs(e, str, &i);
	}
	strfree(&user_dir);
	return (ret);
}
