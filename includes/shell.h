/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:10:33 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/15 21:01:25 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	<unistd.h> :		[ chdir | access ]
**		(ft_chdir)
**	<sys/stat.h> :		[ lstat ]
**		(ft_chdir)
**	<dirent.h> :		[ opendir | readdir ]
**		(ft_exec)
**	<signal.h> :		[ signal ]
**		(ft_signal)
*/

# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include "libft.h"

# define PATH		"/usr/bin:/bin:/usr/sbin:/sbin"

typedef struct		s_env
{
	int				x;
	int				exit;
	char			**env;
	char			*prompt;
	char			*home;
	char			*line;
	char			**cmd;
	size_t			cmd_len;
}					t_env;

int					ft_parse_line(t_env *e);
int					ft_error(char *util, char *msg, char *what);

/*
**		Exec
*/
int					ft_exec(char **cmd, char **env);
char				**ft_find_paths(char **env);
char				*ft_find_exec(char **paths, char *cmd);

/*
**		Init
*/
void				ft_init(t_env *e, int ac, char **av, char **env);

/*
**		Signals
*/
int					ft_handle_ret_signal(int status);
void				ft_set_sig_handler(void);
void				ft_sig_handler(int sig);

/*
**		Tools
*/
int					ft_matchquotes(char *str);
int					ft_issetenv(char **env, char *name);
void				ft_env_free(t_env *e);
char				*ft_find_name(char **env, char *name);
char				*ft_find_value(char **env, char *name);

/*
**		Builtins
*/
void				ft_exit(t_env *e);
int					ft_env(t_env *e);
int					ft_setenv_blt(t_env *e);
int					ft_setenv(char ***env, char *name, char *value);
int					ft_unsetenv_blt(t_env *e);
int					ft_unsetenv(char ***env, char *name);
int					ft_chdir(t_env *e);
int					ft_echo(t_env *e);
int					ft_where(t_env *e);

#endif
