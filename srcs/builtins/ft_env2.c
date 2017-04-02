/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleghmar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:41:20 by aleghmar          #+#    #+#             */
/*   Updated: 2017/04/02 03:18:54 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_invalid_option_env(char s)
{
	ft_putstr_fd("Yoloshell: env: invalid option -- '", 2);
	ft_putchar_fd(s, 2);
	ft_putstr_fd("'\nRTFM ...", 2);
	ft_putstr_fd("\n-i: clean env + own value \"Var=Val\"\n", 2);
	ft_putstr_fd("-u: unset a value\n", 2);
	return (-1);
}

int		ft_env_opt(char *str, int option, t_list **temp_env)
{
	int		i;

	i = 1;
	if (*str != '-')
		return (option);
	while (str[i])
	{
		if (str[i] == 'i')
		{
			option = 1;
			ft_envdel(temp_env);
			if (i > 1)
				return (1);
		}
		else if (str[i] == 'u')
			option = 2;
		else
			return (ft_invalid_option_env(str[i]));
		i++;
	}
	return (option);
}

void	ft_env_set(char **args, t_list **temp_env, int i)
{
	char	*plok[3];

	ft_fill_array((void**)plok, ft_strdup(args[i]), NULL, NULL);
	ft_setenv_user(plok, temp_env, 1);
	ft_array_strdel(plok);
}

int		ft_env_args(char **args, int i, t_list **tmp, int *ret)
{
	int		option;

	option = 0;
	if (*args[i] == '-')
	{
		option = ft_env_opt(args[i], option, tmp);
		if (option == 2 && !args[i + 1])
		{
			option = -1;
			ft_putstr_fd("YoloShell: option requires an argument -- u\n"
				, 2);
		}
	}
	else if (ft_strchr(args[i], '='))
		ft_env_set(args, tmp, i);
	else if (ft_env_opt(args[i - 1], 0, tmp) == 2)
		option = ft_env_unset(args, tmp, i);
	else
	{
		option = -1;
		ft_command(&args[i], *tmp, ret, 0);
		ft_envdel(tmp);
	}
	return (option);
}

int		ft_env(char **args, t_list *env, int *last_ret)
{
	int		i;
	int		exec;
	int		option;
	t_list	*temp_env;

	exec = 0;
	option = 0;
	i = 1;
	if (!args[1])
		return (ft_print_env(env));
	temp_env = ft_lstdup(env);
	while (args[i] && !exec && option != -1)
	{
		option = ft_env_args(args, i, &temp_env, last_ret);
		i++;
	}
	if (option != -1)
		ft_print_env(temp_env);
	ft_envdel(&temp_env);
	return (1);
}
