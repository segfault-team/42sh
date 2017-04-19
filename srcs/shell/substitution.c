#include "shell.h"

static void	substitution_cond(char **str, int *i, char *tmp)
{
	tmp = ft_strdup((*str));
	do_substitution(str, i, USERS_DIR, 0);
	if (access(&(*str)[*i], F_OK) == -1)
	{
		ft_strdel(str);
		*str = tmp;
	}
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
			substitution_cond(str, &i, tmp);
	}
	else if ((*str)[i] == '~' && (i == 0 || (*str)[i - 1] == ' ')
			&& (!(*str)[i + 1] || ((*str)[i + 1] != '~'
			&& (*str)[i + 1] != '\'' && (*str)[i + 1] != '\"')))
	{
		tmp = ft_getenv(e->env, "HOME");
		if (!tmp)
			tmp = ft_strdup(e->home);
		do_substitution(str, &i, tmp, 0);
	}
	ft_strdel(&tmp);
}

int			substitution(t_env *e, char **str)
{
	int		i;
	int		len;
	int		bs;
	char	quote;

	i = -1;
	bs = 0;
	quote = '\0';
	len = (int)ft_strlen(*str);
	if (!(*str))
		return (0);
	while (str && ++i < len && (*str)[i])
	{
		quote = ft_check_quote_bs((*str)[i], quote, bs);
		if (quote != '\'')
		{
			if (i < len && (*str)[i] == '$' && (*str)[i + 1])
				do_env_subs(e, str, &i);
			else
				substitution_tilde(e, str, i);
			len = (int)ft_strlen(*str);
		}
	}
	return (0);
}
