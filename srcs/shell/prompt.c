#include "shell.h"

void		ft_prompt(char *prompt)
{
	ft_putstr(GREEN);
	ft_putstr(prompt);
	ft_putstr(ENDC);
}

static char	*ft_getdir(char *str)
{
	int		len;
	char	*ptr;

	len = ft_strlen(str);
	while (str[len] != '/')
		len--;
	ptr = ft_strdup(&str[len + 1]);
	if (!*ptr)
		*ptr = '/';
	return (ptr);
}

char		*ft_create_prompt(t_env *e, char *prompt)
{
	char	*new_prompt;
	char	*tmp;
	char	str[255];

	new_prompt = ft_getenv(e->env, "PWD");
	if (!new_prompt)
		new_prompt = ft_strdup(getcwd(str, 255));
	tmp = ft_getdir(new_prompt);
	new_prompt = ft_strjoin(tmp, prompt);
	return (new_prompt);
}
