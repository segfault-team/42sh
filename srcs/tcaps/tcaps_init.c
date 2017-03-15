/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 21:25:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/03/05 20:12:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Gets terminal name
*/

int			tcaps_get_term_name(char **env)
{
	char	*term;

	if ((term = ft_getenv(env, "TERM")) == NULL)
	{
		ft_error(SH_NAME, "WARNING", "TERM environment variable is not set");
		term = ft_strdup("=xterm");
	}
	if (tgetent(NULL, "xterm") != 1)
	{
		free(term);
		return (ft_error(SH_NAME, "WARNING", "could not find terminfo database"));
	}
	free(term);
	return (0);
}

/*
**	Sets new termios structure
*/

int			tcaps_set(void)
{
	struct termios	tcs;

	if (tcgetattr(STDIN_FILENO, &tcs) < 0)
		return (ft_error(SH_NAME, "WARNING", "could not find termios structure"));
	tcs.c_cc[VMIN] = 1;
	tcs.c_cc[VTIME] = 0;
	tcs.c_lflag &= ~(ICANON | ECHO);
//	tcs.c_lflag &= ~(ISIG); // blocks INTR QUIT and SUSP
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tcs) < 0)
		return (-1);
	return (0);
}

/*
**	Resets termios structure as default
*/

int			tcaps_reset(void)
{
	struct termios	tcs;
	char			*str;

	if (tcgetattr(STDIN_FILENO, &tcs) < 0)
		return (ft_error(SH_NAME, "could not find termios structure", NULL));
	tcs.c_lflag |= (ICANON | ECHO | ISIG);
//	tcs.c_lflag = ~(ISIG); // blocks INTR QUIT and SUSP
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tcs) < 0)
		return (-1);
	str = tgetstr("ve", NULL);
	tputs(str, 1, dsh_putchar);
	return (0);
}

void			tcaps_init(t_env *e)
{
	e->check_sigtstp = 0;
	NB_MOVE = 0;
	NB_READ = 0;
	TCAPS.check_move = 0;
	TCAPS.hist_move = -1;
	TCAPS.nb_line = 1;
	TCAPS.nb_col = 0;
	// search for term name, if TERM is not set what can we do?
	// duplicating "=xterm" seems not a very good idea...
	tcaps_get_term_name(e->env);
	// sets termios structure for the shell.
	// If cannot, it is a deal, so deal it.
	if (tcaps_set())
	{
		// no termios
		// launching minishell (?)
		return ;
	}
	init_tputs_string(e);
	xputs(TGETSTR_AM);
	xputs(TGETSTR_BW);
}

void            init_tputs_string(t_env *e)
{
	TGETSTR_LE = tgetstr("le", NULL);
	TGETSTR_CE = tgetstr("ce", NULL);
	TGETSTR_DM = tgetstr("dm", NULL);
	TGETSTR_DW = tgetstr("dw", NULL);
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
}
