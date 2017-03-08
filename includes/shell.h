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

# define DEBUG(x) dprintf(2, "%s\n", x)
# define VALUE ft_printf("m:%d | c:%d | w:%d | l:%d\n", TCAPS.nb_move, TCAPS.nb_col, WS_COL, TCAPS.nb_line)

# define UATTR __attribute__((unused))

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
# define ENDC		"\033[;0m"
# define WHITE		"\033[;0m"
# define GREEN		"\033[32m"
# define BLUE		"\033[34m"
# define YELLOW		"\033[33m"
# define ITALIC		"\x1b[3m"
# define SH_NAME	"21sh"
# define PATH		"/usr/bin:/bin:/usr/sbin:/sbin"
# define FD			e->fd
# define BUF		e->buf
# define TCAPS		e->tcaps
# define WIN_WIDTH	e->tcaps.ws.ws_col
# define RED_INDEX	e->i_mag
# define MULTI		e->multiline
//# define ML			e->ml

# define NB_MOVE	TCAPS.nb_move
# define NB_READ	TCAPS.nb_read

# define AND		1
# define OR			2

# define HIST_FILE	"/tmp/.history"
# define STD_PROMPT	"$> "
# define H_PROMPT	"heredoc> "
# define BS_PROMPT	"> "

# define OPENFLAGS	(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
# define ONE_RED_FLAGS (O_RDWR | O_CREAT | O_TRUNC)
# define TWO_RED_FLAGS (O_RDWR | O_CREAT | O_APPEND)

/*
**	DEFINE TCAPS KEYS
*/
# define ARROW_UP	65
# define ARROW_DOWN	66
# define CTRL_D		4
# define CTRL_K		11
# define CTRL_P		16

typedef struct		s_magic
{
	char			*cmd;
	char			*type;
}					t_magic;

typedef struct		s_fd
{
	int				fd[2];
	int				in;
	int				stdin;
	int				stdout;
	int				stderr;
}					t_fd;

typedef struct		s_term
{
//	char			*term_name;
//	struct termios	termos;
//	struct termios	save;
	int				check_move;
	int				hist_move;
	int				nb_move;
	int				nb_read;
  	int				nb_line;
  	int				nb_col;
	struct winsize	ws;
}					t_term;

typedef struct s_logic	t_logic;

struct s_logic
{
	char			**atom;
	int				op;
	t_logic			*next;
};

typedef struct		s_job
{
	pid_t			pid;
	struct s_job	*next;
}					t_job;

typedef struct		s_pid_list
{
	pid_t			pid;
	void			*next;
}					t_pid_list;

typedef struct		s_env
{
	int test;

	t_fd			fd;
	int				x;
	int				exit;
	char			**env;
	char			*prompt;
	char			*home;
	char			*line;
	char			*line_bkp;
	char			**cmd;
	char			***cat;
	size_t			cmd_len;
	size_t			i_mag;
	t_magic			*magic;
	t_logic			*logix;

	//??
	t_pid_list		*pid_list;
	t_pid_list		*actual_pid;
	t_job			*jobs;

	char			buf[3];
	t_term			tcaps;
	char 			**history;
	char			*cut;
	char			*multiline;
	int 			child_running;
	int 			check_ctrl_c;
	int 			check_sigtstp;
}					t_env;

int					ft_parse_line(t_env *e);
int					ft_error(char *util, char *msg, char *what);
void				ft_banner(void);
void				ft_prompt(char *prompt);
void				tcaps_prompt(char *prompt);
t_logic				*ft_split_logic(t_logic * x, char **cmd);
int					ft_waitlogix(t_env *e);
void				ft_freelogic(t_logic *x);

/*
**		Exec
*/
int					ft_exec(char **cmd, t_env *e);
int					ft_exec_cmd(t_env *e, char **cmd);
char				**ft_find_paths(char **env);
char				*ft_find_exec(char **paths, char *cmd);
void				ft_close(int fd);
char				**ft_trim_split_cmd(t_env *e);
int					ft_exec_builtin(t_env *e, char **cmd);
int					ft_is_builtin(char *cmd);

/*
**		Redirections
*/
int					ft_redirect(int oldfd, int newfd);
int					ft_redir_builtin(t_env *e);
int					redir_exec_open(int i, t_env *e);
int					redir_check_red(t_env *e, char *red);
int					redir_fill_output(t_env *e);
int					ft_redirect(int oldfd, int newfd);
void				ft_create_file(t_env *e);
int					isRedirection(t_env *e, int i);
int					isOutputRedir(t_env *e, int i);
int					isRedirPipe(t_env *e, int i);
int					isAggregator(t_env *e, int i);
int					isInputRedir(t_env *e, int i);
int					redirToAggregator(t_env *e);
int					isolateFdDestination(t_env *e);
int					isolateFdSource(t_env *e);
int					findAggregatorType(t_env *e);

/*
**		Init - Reset
*/
void				ft_init(t_env *e, int ac, char **av, char **env);
int					ft_reset_line(t_env *e);

/*
**		Signals
*/
//int					ft_check_signals(int call, int sig);
int					ft_handle_ret_signal(int status);
void				ft_set_sig_handler(void);
void				ft_sig_handler(int sig);
t_env				*env_access(t_env *e);

/*
**		Tools
*/
int					ft_matchquotes(char *str);
char				**ft_split_cmds(char *s, char c);
char				*ft_issetenv(char **env, char *name);
char				*ft_getenv(char **env, char *name);
int					red_strstr(char *str);
void				ft_cut_tab(char **pas_tab, int index);
char				***ft_cmds_split(t_env *e);
//char				*ft_tilde(t_env *e, char *current);
int					ft_subs_tilde(t_env *e);
t_job				*ft_new_job(t_job *next, int pid);
void				strfree(char **str);
void				ft_tabzero(char **dbl_tab, int tab_len);
int					isNumber(char );
int					isOnlyNumbers(char *str);
int 				ft_multiline(t_env *e);

/*
**		History
*/
int					ft_check_file_perm(char *file);
int 				ft_read_history(t_env *e);
void 				ft_check_history(t_env *e);

/*
**		Tcaps Tools
*/
void				xputs(char *tag);
void				move_right(t_env *e);

/*
**		Realloc
*/
char				*ft_realloc_line(t_env *e, char c);
char				*ft_realloc_insert_char(t_env *e, char c);
char				*ft_realloc_delete_char(t_env *e, int pos);
void				ft_realloc_insert_str(t_env *e, char *str);

/*
**		Free
*/
void				ft_free_line(t_env *e);
void				ft_env_free(t_env *e);
void				ft_triple_free(t_env *e);
void				strfree(char **str);


/*
**		Builtins
*/
void				ft_exit(t_env *e);
int					ft_env(t_env *e, char **cmd);
int					ft_setenv_blt(t_env *e, char **cmd);
int					ft_setenv(char ***env, char *name, char *value);
int					ft_unsetenv_blt(t_env *e, char **cmd);
int					ft_unsetenv(char ***env, char *name);
int					ft_chdir(t_env *e, char **cmd);
int					ft_echo(char **args);
int					ft_where(t_env *e, char **cmd);
int					ft_store_history(char *cmd);
int					ft_history(t_env *e);

/*
**		Termcaps
*/
int					dsh_putchar(int c);
int					tcaps_putstr(t_env *e, char *str);
int					is_more_than_a_line(t_env *e);
void				tcaps_init(t_env *e);
int					tcaps_set(void);
int					tcaps_reset(void);
int					tcaps(t_env *e);
int					tcaps_check_key(char buf[3], int a, int b, int c);
int					tcaps_is_printable(char buf[3]);
void				tcaps_history_first_step(t_env *e);
int					tcaps_history_up(t_env *e);
int					tcaps_history_down(t_env *e);
void				tcaps_del_bkw(t_env *e);
void				tcaps_history(t_env *e);
void				tcaps_del_fwd(t_env *e);
void				tcaps_left(t_env *e);
void				tcaps_insert(t_env *e);
void				tcaps_clear(t_env *e);
void				tcaps_ctrl_home(t_env *e);
void				tcaps_recalc_pos(t_env *e);
int					tcaps_rewrite_line(t_env *e, char *str);
void				tcaps_ctrl_arrow(t_env *e);
void				tcaps_ctrl_end(t_env *e);
void				tcaps_cut_paste(t_env *e);
void				clear_cmd(t_env *e);
int					is_paste(char *buf);
int					tcaps_paste(t_env *e, char *buf);
void				tcaps_ctrl_d(t_env *e);

/*
**	Magic struct
*/
t_magic				*struct_strsplit(char const *str, char div);
t_magic				*struct_strsplit_quote(char const *s, char c);
t_magic				*struct_strsplit_wo_quote_bs(char const *s, char c);
int					struct_len(t_magic *magic);
void				magic_free(t_env *e);
void				struct_arg_red(int i, t_env *e);
int					struct_check_cmd(int i, t_env *e);
void				magic_type(t_env *e);
void				magic_realloc(t_env *e);
void				struct_find_red(t_env *e);
int					isMagic(t_env *e, int i);

#endif
