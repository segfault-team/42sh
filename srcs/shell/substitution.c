#include "shell.h"
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

static char	*pre_substitution(char **new, char **ret, char *target, int len)
{
	*new = ft_strnew((int)(ft_strlen(target) + len));
	*ret = *new;
	return (target);
}

static void	simple_replace(char **new, char **target)
{
	**new = **target;
	++(*new);
}

void		do_substitution(char **target, int *curr_pos, char *substitute,
							int jmp)
{
	char	*new;
	char	*tmp;
	char	*ret;
	int		escape;

	escape = **target != '!' ? 1 : 0;
	tmp = pre_substitution(&new, &ret, *target, (int)ft_strlen(substitute));
	while (((*target)) && **target)
	{
		if (*target == &tmp[*curr_pos])
			(!substitute) ? *target += jmp
				: ft_replace_word(&new, substitute, &*target, jmp + 1);
		else
			simple_replace(&new, target);
		(*target)++;
	}
	strfree(&tmp);
	tmp = ft_strtrim(ret);
	*target = substitute && escape
	? escape_specials(tmp, *curr_pos, ft_strlen(substitute)) : ft_strdup(ret);
	ft_strdel(&ret);
	ft_strdel(&tmp);
}

static void	substitution_tilde(t_env *e, char **str, int i)
{
	char			*tmp;

	tmp = NULL;
	if ((*str)[i] == '~' && (*str)[i + 1] && (*str)[i + 1] != ' '
		&& (*str)[i + 1] != '/' && (*str)[i + 1] != '$' && (i == 0
		|| (*str)[i - 1] == ' '))
	{
		if ((tmp = ft_getpath_login(&(*str)[i + 1])))
			do_substitution(str, &i, tmp, ft_strlen(&(*str)[i + 1]));
		else
		{
			tmp = ft_strdup((*str));
			do_substitution(str, &i, USERS_DIR, 0);
			if (access(&(*str)[i], F_OK) == -1)
			{
				ft_strdel(str);
				*str = tmp;
			}
		}
	}
	else if ((*str)[i] == '~' && (i == 0 || (*str)[i - 1] == ' ')
			&& (!(*str)[i + 1] || ((*str)[i + 1] != '~'
			&& (*str)[i + 1] != '\'' && (*str)[i + 1] != '\"')))
	{
		tmp = ft_getenv(e->env, "HOME");
		if (!tmp)
			tmp = ft_strdup(e->home);
		do_substitution(str, &i, tmp, 0);
		ft_strdel(&tmp);
	}
}

int			substitution(t_env *e, char **str)
{
	int		i;
	int		len;

	i = -1;
	len = (int)ft_strlen(*str);
	if (!(*str))
		return (0);
	while (str && ++i < len && (*str)[i])
	{
		if (i < len && (*str)[i] == '$' && (*str)[i + 1])
			do_env_subs(e, str, &i);
		else
			substitution_tilde(e, str, i);
	}
	return (0);
}
