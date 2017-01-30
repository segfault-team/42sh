/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:10:33 by lfabbro           #+#    #+#             */
/*   Updated: 2017/01/28 14:53:07 by kboddez          ###   ########.fr       */
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
**	<fcntl.h> :		[ open | read ]
**		(ft_history.c)
**	<signal.h> :		[ signal ]
**		(ft_signal)

*/

# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include "libft.h"

# define PATH		"/usr/bin:/bin:/usr/sbin:/sbin"
# define FD e.fd
# define BUF e->buf
# define TCAPS e->tcaps

# define OPENFLAGS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

typedef struct		s_fd
{
	int				stdin;
	int				stdout;
	int				stderr;
}					t_fd;

typedef struct		s_term
{
	char			*term_name;
	struct termios	termos;
	struct termios	save;
	int				nb_move;
	int				nb_read;
	int				check_move;
	int				hist_move;
}					t_term;

typedef struct		s_env
{
	t_fd			fd;
	int				x;
	int				exit;
	char			**env;
	char			*prompt;
	char			*home;
	char			*line;
	char			**cmd;
	size_t			cmd_len;
	char			buf[3];
	t_term			tcaps;
	char 			**history;
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
int 				read_history(t_env *e);
void				ft_env_free(t_env *e);
void 				check_history(t_env *e);
char				*ft_issetenv(char **env, char *name);
char				*ft_getenv(char **env, char *name);
char				*realloc_line(t_env *e, char c);
char				*realloc_insert_char(t_env *e, char c);
char				*realloc_delete_char(t_env *e);

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
int					store_history(char **cmd);
int					ft_history(t_env *e);

/*
**		Termcaps
*/
int					check_key(char buf[3], int a, int b, int c);
int					check_read(char buf[3]);
char				*realloc_line(t_env *e, char c);
int					ft_termcaps(t_env *e);
int					dsh_putchar(int c);
void				term_history_up(t_env *e);
int					term_history_down(t_env *e);

#endif
