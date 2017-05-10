/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlistrat <vlistrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:44:14 by vlistrat          #+#    #+#             */
/*   Updated: 2017/05/10 14:28:34 by vlistrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define UATTR __attribute__((unused))

# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft.h"

# include <sys/stat.h>
# include <sys/types.h>

# define CMD_NF			1
# define FILE_NF		2
# define NSFOD			3
# define FAIL			4
# define INVALID_FILE	5
# define DIRCLOSE_FAIL	6
# define PERM_DENIED	7

# define PATH_MAX		2048
# define C_RESET		"\033[39m"
# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_MAGENTA		"\033[35m"
# define C_CYAN			"\033[36m"
# define C_WHITE		"\033[97m"
# define C_EXEC			C_RED
# define C_FIFO			C_YELLOW
# define C_CHR			C_YELLOW
# define C_DIR			C_CYAN
# define C_BLK			C_BLUE
# define C_REG			C_RESET
# define C_LNK			C_MAGENTA
# define C_SOCK			C_GREEN
# define C_WHT			C_WHITE

# define RED			"\033[31m"
# define ENDC			"\033[;0m"
# define WHITE			"\033[;0m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define YELLOW			"\033[33m"
# define ITALIC			"\x1b[3m"
# define SH_NAME		"42sh"
# define PATH			"/usr/bin:/bin:/usr/sbin:/sbin"
# define USERS_DIR		"/Users/"
# define FD				e->fd
# define BUF			e->buf
# define TCAPS			e->tcaps
# define WIN_WIDTH		e->tcaps.ws.ws_col
# define RED_INDEX		e->i_mag
# define MULTI			e->multiline
# define HIST_MOVE 		TCAPS.hist_move
# define NB_COL 		TCAPS.nb_col
# define NB_LINE 		TCAPS.nb_line
# define CHECK_MOVE 	TCAPS.check_move
# define ERRCODE		e->errcode
# define ERRMSG			e->err_msg
# define DP				e->dp
# define DIRP			e->dirp

# define NB_MOVE		TCAPS.nb_move
# define NB_READ		TCAPS.nb_read

# define AND			1
# define OR				2

# define STD_PROMPT		" $> "
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
# define OPERATOR		4
# define HEREDOC		5

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
# define TGETSTR_ME		e->struct_tputs.me
# define TGETSTR_MR		e->struct_tputs.mr
# define TGETSTR_UP		e->struct_tputs.up

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
	char				*me;
	char				*mr;
	char				*up;
}						t_tputs;

typedef struct			s_opt_hist
{
	int					a : 2;
	int					c : 2;
	int					d : 2;
	int					i_opt_d;
	int					h : 2;
	int					w : 2;
	int					r : 2;
	int					p : 2;
}						t_opt_hist;

typedef struct			s_aggre_elems
{
	int					nb_chevron;
	int					nb_ampersand;
	int					type;
}						t_aggre_elems;

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

typedef struct			s_file
{
	char				*name;
	char				*color;
}						t_file;

typedef struct			s_hash
{
	unsigned int		hash;
	char				*name;
	struct s_hash		*next;
}						t_hash;

typedef struct			s_pos
{
	int					i;
	int					j;
}						t_pos;

typedef struct			s_env
{
	t_fd				fd;
	int					x;
	struct termios		*new_term;
	struct termios		*old_term;
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
	size_t				len_mag;
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
	int					check_input;
	t_tputs				struct_tputs;
	char				*hist_file;
	size_t				trunc_in_history;
	char				quote;
	t_file				**files;
	char				*prefix;
	char				*path;
	int					selected;
	size_t				total_len;
	int					c_match;
	int					start;
	int					printed;
	int					row;
	char				*heredoc;
	t_list				*hdoc;
	t_list				*b_hdoc;
	int					herestop;
	char				*herestock;
	char				**hdoc_words;
	int					hdoc_nb;
	int					raw;
	int					is_out_close;
	int					hdoc_index;
	int					last_cmd_ret;
	int					last_pipe_ret;
	char				multi_quote;
	char				*susp;
	int					env_exec;
	int					errcode;
	char				*err_msg;
	int					mult_esc;
	int					is_builtin;
	t_hash				*hash;
	int					cmd_ok;
	struct dirent		*dp;
	DIR					*dirp;
}						t_env;

/*
** MISC
*/
int						manage_operators(t_env *e, int i, int ret);
int						ft_waitlogix(t_env *e);
int						ft_parse_line(t_env *e);
int						ft_error(char *util, char *msg, char *what);
int						ft_error2(char *msg, char *msg2, char *msg3, \
									char *msg4);
void					ft_banner(void);
void					ft_prompt(char *prompt);
int						ft_freelogic(t_logic *x);
t_logic					*ft_split_logic(t_logic *x, char **cmd);
t_logic					*ft_new_logic(void);
int						ft_check_op(char *s);
int						substitution(t_env *e, char **target, char quote,
							int bs);
int						manage_exclamation_mark(t_env *e, int *curr_pos);
int						error_em(char *arg, char *sh_name);
int						manage_double_excl_mark(t_env *e, int *curr_pos);
int						join_line(t_env *e, int *curr_pos);
void					do_substitution(char **target, int *curr_pos, \
										char *subsitute, int nb_char_to_jump);
void					do_substitution_no_esc(char **target, int *curr_pos, \
										char *subsitute, int nb_char_to_jump);
int						do_env_subs(t_env *e, char **target, int *curr);
int						manage_err(t_env *e);
void					set_error(t_env *e, int errcode, char *err_msg);
void					free_error(t_env *e);

/*
**		Exec
*/
int						ft_exec_builtin(t_env *e, char **cmd, int ret);
int						ft_exec_bis(char **cmd, t_env *e, char *exec, int ret);
int						ft_fork_exec(char *exec, char **cmd, t_env *e);
int						ft_waitsons(t_env *e);
int						ft_is_builtin(char *cmd);
char					*ft_find_exec_readdir(char *paths, char *cmd);
int						ft_exec_cmd(t_env *e, char **cmd);
char					**ft_find_paths(char **env);
int						print_command_not_found(char *cmd, t_env *e);
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
int						is_redir_sign(char c);
int						is_redirection(t_env *e, int i);
int						is_output_redir(t_env *e, int i);
int						find_next_output(t_env *e, int i);
int						find_last_pipe(t_env *e);
int						is_redir_pipe(t_env *e, int i);
int						is_aggregator(t_env *e, int i);
int						is_input_redir(t_env *e, int i);
int						redir_to_aggregator(t_env *e);
int						isolate_fd_destination(t_env *e, int *is_file);
int						isolate_fd_source(t_env *e);
int						is_redir_from_symbol(t_env *e, int i);
int						find_aggregator_type(t_env *e);
int						is_next_redir(t_env *e, int i);
void					ft_create_file(t_env *e);
int						redirection_before_cmd(t_env *e);
int						is_input_file(t_env *e, int i);
int						redir_input(t_env *e);
int						is_redir_from_symbol(t_env *e, int i);
int						is_input_in_next_cmd(t_env *e, int i);
int						is_heredoc(t_env *e, int i);
int						redir_from_hdoc(t_env *e);
int						is_put_after(t_env *e);
int						is_operator(t_env *e, int i);
int						is_and(t_env *e, int i);
int						is_or(t_env *e, int i);
int						find_nxt_operator(t_env *e);
int						ft_dupp(t_env *e);
void					output_aggre(t_env *e, int fd_src, int fd_dst,
							int is_file);
void					close_aggre(t_env *e, int fd_src);
int						space_after_aggre(char *s);
int						is_output_after(t_env *e, int i);
int						is_special_aggre(t_env *e, int i);
int						is_special_aggre_in_line(t_env *e, int i);
int						is_invalid_spe_aggre(t_env *e, int i);

/*
**		Init - Reset
*/
int						ft_reset_line(t_env *e);
int						ft_init(t_env *e, char **env);
int						ft_set_home(t_env *e, char *path);
void					ft_set_shlvl(t_env *e);

/*
**		Signals
*/
int						ft_handle_ret_signal(int status);
void					ft_set_sig_handler(void);
void					ft_sig_handler(int sig);
void					ft_sigint(t_env *e);
t_env					*env_access(t_env *e);

/*
**		Tools
*/
int						ft_pairs(char *str);
int						check_pairs(char *str, char c, char d);
int						ft_matchquotes(char *str);
int						red_strstr(char *str);
int						ft_subs_tilde(t_env *e);
int						is_number(char c);
int						is_only_numbers(char *str);
int						ft_multiline(t_env *e);
char					*is_bad_line(char *line, char quote);
char					check_quote(t_env *e, char *s);
char					*ft_strdup_wo_quote_bs(char *s);
int						ft_isspace(char c);
int						ft_start_with(char *str, char *comp);
int						open_file(char *file, int flags, mode_t mode);
int						atoi_bis(const char *str);
int						check_last_char(t_env *e, char c);
int						check_prev_last_char(t_env *e, char c);
int						ft_heredoc(t_env *e);
char					**ft_split_cmds(char const*s, char c);
char					**new_tabcat(char ***oldtab, char **str);
char					*ft_issetenv(char **env, char *name);
char					*ft_getenv(char **env, char *name);
char					***ft_cmds_split(t_env *e);
void					ft_cut_tab(char **pas_tab, int index);
void					strfree(char **str);
void					ft_tabzero(char **dbl_tab, int tab_len);
t_job					*ft_new_job(t_job *next, int pid);
int						store_heredoc(t_env *e);
int						token_error(t_env *e, int id);
int						is_last_cmd(t_env *e, int i);
int						ft_catlen(char ***cat);
char					*ft_xtoa(intmax_t nb);
char					*ft_getpath_uid(int uid, char *path);
char					*ft_getpath_login(char *login);
void					init_opt_hist(t_opt_hist *opt);
int						get_hist_options(int i, char **cmd, t_opt_hist *opt);
int						exit_in_read(t_env *e);
int						child_is_signaled(int status);

/*
**		History
*/
int						ft_history(t_env *e, char **cmd, int i);
int						ft_check_file_perm(char *file);
int						ft_read_history(t_env *e);
int						ft_write_history(t_env *e, int flag);
char					**delete_line_in_tab(char **ttab, int d);
void					ft_store_history(t_env *e);

int						history_delete(t_env *e, char **cmd, int i);
int						print_history(t_env *e, char **cmd);
int						clear_history_list(t_env *e);
int						append_history_file_in_list(t_env *e);
int						print_history_help(void);
int						history_error_with_id(char **cmd, char *sh_name, \
							int id);

/*
**		Tcaps Tools
*/
void					xputs(char *tag);
void					move_right(t_env *e);
int						tcaps_enter(t_env *e);

/*
**		Realloc
*/
char					*ft_realloc_line(t_env *e, char c);
char					*ft_realloc_insert_char(t_env *e, char c);
char					*ft_realloc_delete_char(t_env *e, int pos);
char					*ft_delete_char(char *str, int pos);
char					*convert_tabs(char *str);
void					ft_realloc_insert_str(t_env *e, char *str);
int						detect_tabs(char *str, int *i, int *j);

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
int						ft_env_error(char *cmd);
int						ft_insert_arg(char ***env_cpy, char *arg);
int						ft_env_opt_u_error(char *cmd);
int						ft_cat_env_args(char ***env_cpy, char **cmd, int *i);
int						ft_setenv_blt(t_env *e, char **cmd);
int						ft_setenv(char ***env, char *name, char *value);
int						ft_unsetenv_blt(t_env *e, char **cmd);
int						ft_unsetenv(char ***env, char *name);
int						ft_cd(t_env *e, char **cmd);
int						ft_pwd(t_env *e, char **cmd);
int						ft_echo(char **args);
int						ft_where(t_env *e, char **cmd);
int						ft_exit(t_env *e, char **cmd);
int						manage_opt_hist_priority(t_opt_hist *opt);
int						is_valid_opt(char c);
void					add_opt(t_opt_hist *opt, char c, int *opt_d, int i);
int						history_p(t_env *e, char **cmd);

/*
**		Termcaps
*/
int						reading(t_env *e);
void					read_input(t_env *e);
int						is_paste(char *buf);
int						tcaps_paste(t_env *e, char *buf);
int						dsh_putchar(int c);
int						tcaps_putstr(t_env *e, char *str);
int						is_more_than_a_line(t_env *e);
int						tcaps_set(t_env *e);
int						tcaps_reset(t_env *e);
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
void					print_new_cmd_from_history(t_env *e);
void					print_last_cmd(t_env *e);
int						locate_history(char **history, int c_pos, \
							char *comp, int dir);
void					tcaps_ctrl_d(t_env *e);
void					init_tputs_string(t_env *e);
int						tcaps_init(t_env *e);
void					tcaps_history_first_step(t_env *e);

/*
**	Magic struct
*/
int						struct_len(t_magic **magic);
int						is_magic(t_env *e, int i);
int						struct_check_cmd(int i, t_env *e);
void					magic_free(t_env *e);
void					struct_arg_red(int i, t_env *e);
int						magic_type(t_env *e);
void					magic_realloc(t_env *e);
void					struct_find_red(t_env *e);
t_magic					*struct_strsplit_quote_bs(char const *s, char c);
t_magic					*struct_strsplit_wo_quote_bs(char const *s, char c);
void					struct_init(int len, t_magic *magic);
int						is_redit_sign(char c);
int						ft_check_input(int i, t_env *e);
int						ft_check_output(int i, t_env *e);
int						ft_check_heredoc(int i, t_env *e);
int						check_magic_red(t_env *e);
int						check_magic_content(t_env *e, int i);

/*
**		Auto Completion
*/
int						auto_completion(t_env *e);
char					**get_valid_content_from_path(t_env *e, \
							char *curr_path, char *arg, int type);
void					print_auto_completion(t_env *e, char *arg, \
							char *path, char **content);
void					ft_putstr_spec(t_env *e, char *str);
int						valid_selection(t_env *e);
void					tcaps_manage_printable_char(t_env *e);
int						tcaps_is_delete_key(t_env *e);
int						cur_inquote(char *str, int pos);
void					complete_arg(t_env *e, char *arg, int type);
char					*ft_pick_color(char *perm);
char					ft_file_type(int mode);
char					*ft_perms(int mode);
char					*get_path_from_arg(t_env *e, char *arg, int type);
char					*isolate_arg_to_complete(char *arg);
int						ft_is_dir(char *target);
int						test_file(char *curr_path, char *curr_file,
							int exec_only);
void					ft_add_list(t_list **first, t_list **ptr, char *str);
void					ft_put_file(t_env *e, int i, char *spaces);
void					ft_fill_files(char **argv, t_env *e);
int						ft_countchar(char *str, char c);
int						ft_countstr(char *str, char *cmp);
int						calc_rows(t_env *e);
void					merge_sort(t_list **source);
char					*escape_specials(char *str, int i, int len);
t_list					*pick_destination(t_env *e, char *curr_path, char *arg,
							int type);

/*
**      Parse Command
*/
int						parse_command(t_env *e);
void					check_parsing_simple(t_env *e, int *i, char c);
int						check_parsing_double(t_env *e, int *i, char c);
void					check_parsing_ampersand(t_env *e, int *i);
void					insert_char(t_env *e, char c, int pos);
void					insert_char_in_line(char **str, char c, int pos);
void					delete_char(t_env *e, int pos);

/*
**		Chdir
*/
int						ft_pre_chdir(char **tmp, char *dir, t_env *e);
int						ft_chdir_error(char *path);
int						ft_cd_check_option(char ***argv);
char					*ft_save_oldpwd(t_env *e);
char					*ft_create_path(char **paths, int process);
char					*ft_repstr(char *s1, char *s2, t_env *e);
void					ft_fill_array(void **array, void *a1, void *a2, \
							void *a3);
void					ft_array_strdel(char **array);
void					ft_remove_usless_slash(char *str);
void					ft_replace_word(char **s1, char *s2, char **s3, int i);

char					*ft_create_prompt(t_env *e, char *prompt);
int						ft_is_escaped(char *str, int i);
int						ft_is_escape_after(char *str, int i);

/*
** HASH
*/
void					hash_gen(t_env *e, char **paths);

#endif
