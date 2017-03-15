#include "shell.h"

int         ft_check_file_perm(char *file)
{
	int     ret;

	ret = 0;
	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK) == -1)
		{
			ft_error(SH_NAME, "Cannot access file for reading", file);
			ret = -1;
		}
		if (access(file, W_OK) == -1)
		{
			ft_error(SH_NAME, "Cannot access file for writing", file);
			ret = -1;
		}
	}
	return (ret);
}

int			ft_matchquotes(char *s)
{
	int		i;
	int		bs;
	char	quote;

	i = 0;
	bs = 0;
	quote = '\0';
	while (s[i])
	{
		if (!bs && s[i] == '\\' && quote != '\'')
			bs = 1;
		else
		{
			if (quote == '\0' && !bs && (s[i] == '\'' || s[i] == '\"'))
				quote = s[i];
			else if (s[i] == quote && ((!bs && quote == '\"') || quote == '\''))
				quote = '\0';
			bs = 0;
		}
		++i;
	}
	if (quote != '\0')
		return (0);
	return (1);
}

char		*ft_issetenv(char **env, char *name)
{
	char	*eval;
	int		i;

	i = -1;
	eval = ft_strjoin(name, "=");
	if (env)
	{
		while (env[++i])
		{
			if (ft_strnequ(env[i], eval, ft_strlen(eval)))
			{
				free(eval);
				return (env[i]);
			}
		}
	}
	free(eval);
	return (NULL);
}

char		*ft_getenv(char **env, char *name)
{
	char	*value;
	char	*tmp;

	value = NULL;
	tmp = NULL;
	if ((tmp = ft_issetenv(env, name)) != NULL)
	{
		value = ft_strdup(ft_strchr(tmp, '=') + 1);
	}
	return (value);
}
