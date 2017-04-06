#include "shell.h"

/*
**	Gets terminal name
*/

int		tcaps_get_term_name(char **env, int raw)
{
	char	*term;

	if ((term = ft_getenv(env, "TERM")) == NULL)
	{
		if (!raw)
			ft_error("WARNING", "TERM environment variable is not set", NULL);
		term = ft_strdup("xterm");
	}
	if (tgetent(NULL, term) != 1)
	{
		strfree(&term);
		if (!raw)
			ft_error("WARNING", "could not find terminfo database", NULL);
		return (-1);
	}
	strfree(&term);
	return (0);
}

/*
**	Sets new termios structure
*/

int		tcaps_set(t_env *e)
{
	if (!isatty(STDIN_FILENO))
		return (-1);
	if (tcgetattr(STDIN_FILENO, e->new_term) < 0)
	{
		if (e && !e->raw)
			ft_error("WARNING", "could not find termios structure", NULL);
		return (-1);
	}
	ft_memcpy(e->old_term, e->new_term, sizeof(struct termios));
	e->new_term->c_cc[VMIN] = 1;
	e->new_term->c_cc[VTIME] = 0;
	e->susp[0] = e->new_term->c_cc[VSUSP];
	e->new_term->c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW, e->new_term) < 0)
		return (-1);
	return (0);
}

/*
**	Resets termios structure as default
*/

int		tcaps_reset(t_env *e)
{
	if (!e->raw && tcsetattr(STDIN_FILENO, TCSANOW, e->old_term) < 0)
		return (-1);
	xputs(TGETSTR_VE);
	return (0);
}

int		tcaps_init(t_env *e)
{
	int ret;

	ret = 0;
	e->check_sigtstp = 0;
	NB_MOVE = 0;
	NB_READ = 0;
	TCAPS.check_move = 0;
	TCAPS.hist_move = -1;
	TCAPS.nb_line = 1;
	TCAPS.nb_col = 0;
	tcaps_get_term_name(e->env, e->raw);
	if (tcaps_set(e))
		ret = -1;
	else
		ft_banner();
	init_tputs_string(e);
	xputs(TGETSTR_AM);
	xputs(TGETSTR_BW);
	return (ret);
}

void	init_tputs_string(t_env *e)
{
	TGETSTR_LE = tgetstr("le", NULL);
	TGETSTR_CE = tgetstr("ce", NULL);
	TGETSTR_DM = tgetstr("dm", NULL);
	TGETSTR_DW = tgetstr("do", NULL);
	TGETSTR_CR = tgetstr("cr", NULL);
	TGETSTR_ND = tgetstr("nd", NULL);
	TGETSTR_CL = tgetstr("cl", NULL);
	TGETSTR_VI = tgetstr("vi", NULL);
	TGETSTR_VE = tgetstr("ve", NULL);
	TGETSTR_CD = tgetstr("cd", NULL);
	TGETSTR_DC = tgetstr("dc", NULL);
	TGETSTR_ED = tgetstr("ed", NULL);
	TGETSTR_AM = tgetstr("am", NULL);
	TGETSTR_BW = tgetstr("bw", NULL);
	TGETSTR_IM = tgetstr("im", NULL);
	TGETSTR_EI = tgetstr("ei", NULL);
	TGETSTR_SC = tgetstr("sc", NULL);
	TGETSTR_DL = tgetstr("dl", NULL);
	TGETSTR_RC = tgetstr("rc", NULL);
	e->struct_tputs.me = tgetstr("me", NULL);
	e->struct_tputs.mr = tgetstr("mr", NULL);
	e->struct_tputs.up = tgetstr("up", NULL);
}
