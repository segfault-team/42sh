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

# define RED			"\033[31m"
# define ENDC			"\033[;0m"
# define WHITE			"\033[;0m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define YELLOW			"\033[33m"
# define ITALIC			"\x1b[3m"
# define SH_NAME		"21sh"
# define PATH			"/usr/bin:/bin:/usr/sbin:/sbin"
# define FD				e->fd
# define BUF			e->buf
# define TCAPS			e->tcaps
# define WIN_WIDTH		e->tcaps.ws.ws_col
# define RED_INDEX		e->i_mag
# define MULTI			e->multiline

# define NB_MOVE		TCAPS.nb_move
# define NB_READ		TCAPS.nb_read

# define AND			1
# define OR				2

# define STD_PROMPT		"$> "
# define H_PROMPT		"heredoc> "
# define BS_PROMPT		"> "
# define HIST_NAME		"/.sh_history"
# define HIST_FILE		e->hist_file

# define OFLAGS		(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
# define ONE_RED_FLAGS 	(O_RDWR | O_CREAT | O_TRUNC)
# define TWO_RED_FLAGS 	(O_RDWR | O_CREAT | O_APPEND)

/*
**	DEFINE TCAPS KEYS
*/
# define ARROW_UP		65
# define ARROW_DOWN		66
# define CTRL_D			4
# define CTRL_K			11
# define CTRL_P			16

/*
**	DEFINE REDIRECTION
*/
# define PIPE			0
# define AGGREGATOR		1
# define OUTPUT			2
# define INPUT			3

/*
**	TPUTS STING DEFINE
*/
# define TGETSTR_LE 	e->struct_tputs.le
# define TGETSTR_CE 	e->struct_tputs.ce
# define TGETSTR_DM 	e->struct_tputs.dm
# define TGETSTR_DW 	e->struct_tputs.dw
# define TGETSTR_CR 	e->struct_tputs.cr
# define TGETSTR_ND 	e->struct_tputs.nd
# define TGETSTR_CL 	e->struct_tputs.cl
# define TGETSTR_VI 	e->struct_tputs.vi
# define TGETSTR_VE 	e->struct_tputs.ve
# define TGETSTR_CD 	e->struct_tputs.cd
# define TGETSTR_DC 	e->struct_tputs.dc
# define TGETSTR_ED 	e->struct_tputs.ed
# define TGETSTR_AM 	e->struct_tputs.am
# define TGETSTR_BW 	e->struct_tputs.bw
# define TGETSTR_IM 	e->struct_tputs.im
# define TGETSTR_EI 	e->struct_tputs.ei
# define TGETSTR_SC 	e->struct_tputs.sc
# define TGETSTR_DL 	e->struct_tputs.dl
# define TGETSTR_RC 	e->struct_tputs.rc

typedef struct			s_tputs
{
	char				*le;
	char				*ce;
	char				*dm;
	char				*dw;
	char				*cr;
	char				*nd;
	char				*cl;
	char				*vi;
	char				*ve;
	char				*cd;
	char				*dc;
	char				*ed;
	char				*am;
	char				*bw;
	char				*im;
	char				*ei;
	char				*sc;
	char				*dl;
	char				*rc;
}						t_tputs;

typedef struct			s_magic
{
	char				*cmd;
	char				*type;
}						t_magic;

typedef struct			s_fd
{
	int					fd[2];
	int					in;
	int					stdin;
	int					stdout;
	int					stderr;
}						t_fd;

typedef struct			s_term
{
/*	char				*term_name;
	struct termios		termos;
	struct termios		save;*/
	int					check_move;
	int					hist_move;
	int					nb_move;
	int					nb_read;
	int					nb_line;
	int					nb_col;
	struct winsize		ws;
}						t_term;

typedef struct			s_logic
{
	char				**atom;
	int					op;
	struct s_logic		*next;
}						t_logic;

typedef struct			s_job
{
	pid_t				pid;
	struct s_job		*next;
}						t_job;

typedef struct			s_pid_list
{
	pid_t				pid;
	void				*next;
}						t_pid_list;

typedef struct			s_env
{
	t_fd				fd;
	int					x;
	int					exit;
	char				**env;
	char				*prompt;
	char				*home;
	char				*line;
	char				*line_bkp;
	char				**cmd;
	char				***cat;
	size_t				cmd_len;
	size_t				i_mag;
	t_magic				*magic;
	t_logic				*logix;
	t_pid_list			*pid_list;
	t_pid_list			*actual_pid;
	t_job				*jobs;
	char				buf[3];
	t_term				tcaps;
	char				**history;
	char				*cut;
	char				*multiline;
	int					child_running;
	int					check_ctrl_c;
	int					check_sigtstp;
	t_tputs				struct_tputs;
	char				*hist_file;
	size_t				trunc_in_history;
}						t_env;


/*
**
*/
int						ft_waitlogix(t_env *e);
int						ft_parse_line(t_env *e);
int						ft_error(char *util, char *msg, char *what);
void					ft_banner(void);
void					ft_prompt(char *prompt);
void					tcaps_prompt(char *prompt);
void					ft_freelogic(t_logic *x);
t_logic					*ft_split_logic(t_logic *x, char **cmd);
int						substitution(t_env *e);
int						manage_exclamation_mark(t_env *e, int *curr_pos);
void					do_substitution(t_env *e, int *curr_pos, \
										char *subsitute, int nb_char_to_jump);

/*
**		Exec
*/
int						ft_exec_builtin(t_env *e, char **cmd);
int						ft_is_builtin(char *cmd);
int						ft_exec(char **cmd, t_env *e);
int						ft_exec_cmd(t_env *e, char **cmd);
char					**ft_find_paths(char **env);
char					*ft_find_exec(char **paths, char *cmd);
char					**ft_trim_split_cmd(t_env *e);
void					ft_close(int fd);

/*
**		Redirections
*/
int						ft_redirect(int oldfd, int newfd);
int						ft_redir_builtin(t_env *e);
int						redir_exec_open(int i, t_env *e);
int						redir_check_red(t_env *e, char *red);
int						redir_fill_output(t_env *e);
int						ft_redirect(int oldfd, int newfd);
int						is_redirection(t_env *e, int i);
int						is_output_redir(t_env *e, int i);
int						is_redir_pipe(t_env *e, int i);
int						is_aggregator(t_env *e, int i);
int						is_input_redir(t_env *e, int i);
int						redir_to_aggregator(t_env *e);
int						isolate_fd_destination(t_env *e);
int						isolate_fd_source(t_env *e);
int						find_aggregator_type(t_env *e);
int						is_next_redir(t_env *e, int i);
void					ft_create_file(t_env *e);

/*
**		Init - Reset
*/
int						ft_reset_line(t_env *e);
void					ft_init(t_env *e, int ac, char **av, char **env);

/*
**		Signals
*/
//int					ft_check_signals(int call, int sig);
int						ft_handle_ret_signal(int status);
void					ft_set_sig_handler(void);
void					ft_sig_handler(int sig);
t_env					*env_access(t_env *e);

/*
**		Tools
*/
int						ft_matchquotes(char *str);
int						red_strstr(char *str);
int						ft_subs_tilde(t_env *e);
int						is_number(char c);
int						is_only_numbers(char *str);
int						ft_multiline(t_env *e);
char					**ft_split_cmds(char *s, char c);
char					*ft_issetenv(char **env, char *name);
char					*ft_getenv(char **env, char *name);
char					***ft_cmds_split(t_env *e);
void					ft_cut_tab(char **pas_tab, int index);
void					strfree(char **str);
void					ft_tabzero(char **dbl_tab, int tab_len);
t_job					*ft_new_job(t_job *next, int pid);
int						ft_start_with(char *str, char *comp);

/*
**		History
*/
int						ft_check_file_perm(char *file);
int						ft_read_history(t_env *e);
int						ft_write_history(t_env *e, int flag);
char					**delete_line_in_tab(char **ttab, int d);
void					ft_store_history(t_env *e);

void					history_delete(t_env *e, char **cmd);
void					print_history(t_env *e, char **cmd);
void					clear_history_list(t_env *e);
int						append_history_file_in_list(t_env *e);
void					print_history_help(void);


/*
**		Tcaps Tools
*/
void					xputs(char *tag);
void					move_right(t_env *e);

/*
**		Realloc
*/
char					*ft_realloc_line(t_env *e, char c);
char					*ft_realloc_insert_char(t_env *e, char c);
char					*ft_realloc_delete_char(t_env *e, int pos);
void					ft_realloc_insert_str(t_env *e, char *str);

/*
**		Free
*/
void					ft_free_line(t_env *e);
void					ft_env_free(t_env *e);
void					ft_triple_free(t_env *e);
void					strfree(char **str);

/*
**		Builtins
*/
int						ft_env(t_env *e, char **cmd);
int						ft_setenv_blt(t_env *e, char **cmd);
int						ft_setenv(char ***env, char *name, char *value);
int						ft_unsetenv_blt(t_env *e, char **cmd);
int						ft_unsetenv(char ***env, char *name);
int						ft_chdir(t_env *e, char **cmd);
int						ft_echo(char **args);
int						ft_where(t_env *e, char **cmd);
int						ft_history(t_env *e, char **cmd);
void					ft_exit(t_env *e);

/*
**		Termcaps
*/
int						is_paste(char *buf);
int						tcaps_paste(t_env *e, char *buf);
int						dsh_putchar(int c);
int						tcaps_putstr(t_env *e, char *str);
int						is_more_than_a_line(t_env *e);
int						tcaps_set(void);
int						tcaps_reset(void);
int						tcaps(t_env *e);
int						tcaps_check_key(char buf[3], int a, int b, int c);
int						tcaps_is_printable(char buf[3]);
int						tcaps_history_up(t_env *e);
int						tcaps_history_down(t_env *e);
int						tcaps_rewrite_line(t_env *e, char *str);
void					tcaps_del_bkw(t_env *e);
void					tcaps_history(t_env *e);
void					tcaps_del_fwd(t_env *e);
void					tcaps_left(t_env *e);
void					tcaps_insert(t_env *e);
void					tcaps_clear(t_env *e);
void					tcaps_ctrl_home(t_env *e);
void					tcaps_recalc_pos(t_env *e);
void					tcaps_ctrl_arrow(t_env *e);
void					tcaps_ctrl_end(t_env *e);
void					tcaps_cut_paste(t_env *e);
void					clear_cmd(t_env *e);
void					tcaps_ctrl_d(t_env *e);
void					init_tputs_string(t_env *e);
void					tcaps_init(t_env *e);
void					tcaps_history_first_step(t_env *e);

/*
**	Magic struct
*/
int						struct_len(t_magic *magic);
int						is_magic(t_env *e, int i);
int						struct_check_cmd(int i, t_env *e);
void					magic_free(t_env *e);
void					struct_arg_red(int i, t_env *e);
void					magic_type(t_env *e);
void					magic_realloc(t_env *e);
void					struct_find_red(t_env *e);
t_magic					*struct_strsplit(char const *str, char div);
t_magic					*struct_strsplit_quote(char const *s, char c);
t_magic					*struct_strsplit_wo_quote_bs(char const *s, char c);

#endif
