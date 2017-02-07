/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:10:33 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/06 18:48:17 by lfabbro          ###   ########.fr       */
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

# define DEBUG(x) ft_printf("%d\n", x)
# define VALUE ft_printf("m:%d | c:%d | w:%d | l:%d\n", TCAPS.nb_move, TCAPS.nb_col, WS_COL, TCAPS.nb_line)

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

# define RED		"\033[31m"
# define WHITE		"\033[;0m"
# define GREEN		"\033[32m"
# define BLUE		"\033[34m"
# define YELLOW		"\033[33m"
# define ITALIC		"\x1b[3m"
# define SH_NAME	"21sh"
# define PATH		"/usr/bin:/bin:/usr/sbin:/sbin"
# define FD			e.fd
# define BUF		e->buf
# define TCAPS		e->tcaps
//# define WS_COL		e->tcaps.ws.ws_col

# define WS_COL		TCAPS.ws.ws_col
# define OPENFLAGS	(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

typedef struct		s_magic
{
	char			*cmd;
	char			*type;
}					t_magic;

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
  	int				nb_line;
  	int				nb_col;
 	 struct winsize			ws;
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
	char			***cat;
	size_t			cmd_len;

	int				check_remove_tab;
	t_magic			*magic;

	char			buf[3];
	t_term			tcaps;
	char 			**history;
	char			*cut;
}					t_env;

int					ft_parse_line(t_env *e);
int					ft_error(char *util, char *msg, char *what);
void				ft_banner(t_env *e);

/*
**		Exec
*/
int					ft_exec(char **cmd, char **env, int in, int fd[2]);
char				**ft_find_paths(char **env);
char				*ft_find_exec(char **paths, char *cmd);

/*
**		Init - Reset
*/
void				ft_init(t_env *e, int ac, char **av, char **env);
int					ft_reset_line(t_env *e);

/*
**		Signals
*/
int					ft_handle_ret_signal(int status);
void				ft_set_sig_handler(void);
void				ft_sig_handler(int sig);

/*
**		Tools
*/
int					ft_check_ctrlc(int ctrlc);
int					ft_matchquotes(char *str);
int 				ft_read_history(t_env *e);
void				ft_env_free(t_env *e);
void 				ft_check_history(t_env *e);
char				*ft_issetenv(char **env, char *name);
char				*ft_getenv(char **env, char *name);
void				move_right(t_env *e);
int					red_strstr(char *str);
void				ft_remove_tab(char **pas_tab, int index, int check);
void				ft_cut_tab(char **pas_tab, int index);
char				***ft_cmds_split(t_env *e);
void				ft_triple_free(t_env *e);

/*
**		Realloc
*/
char				*ft_realloc_line(t_env *e, char c);
char				*ft_realloc_insert_char(t_env *e, char c);
char				*ft_realloc_delete_char(t_env *e);
void				ft_realloc_insert_str(t_env *e, char *str);

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
int					ft_store_history(char **cmd);
int					ft_history(t_env *e);

/*
**		Termcaps
*/
int					dsh_putchar(int c);
int					tcaps(t_env *e);
int					tcaps_check_key(char buf[3], int a, int b, int c);
int					tcaps_check_read(char buf[3]);
void				tcaps_history_up(t_env *e);
int					tcaps_history_down(t_env *e);
void				tcaps_del(t_env *e);
void				tcaps_del_fwd(t_env *e);
void				tcaps_history(t_env *e);
void				tcaps_right(t_env *e);
void				tcaps_left(t_env *e);
void				tcaps_insert(t_env *e);
void				tcaps_clear(t_env *e);
void				tcaps_ctrl_home(t_env *e);
void				tcaps_recalc_pos(t_env *e);
int					tcaps_putstr(t_env *e, char *str);
void				tcaps_ctrl_mov(t_env *e);
void				tcaps_ctrl_end(t_env *e);
void				xputs(char *tag);
void				tcaps_cut_paste(t_env *e);
void				clear_cmd(t_env *e);

/*
**	Magic struct
*/
t_magic				*struct_strsplit(char const *str, char div);
t_magic				*struct_strsplit_quote(char const *s, char c);
int					struct_len(t_magic *magic);
void				magic_free(t_env *e);
void				struct_arg_red(int i, t_env *e);
int					struct_check_cmd(int i, t_env *e);
void				magic_type(t_env *e);
void				magic_realloc(t_env *e);

#endif
