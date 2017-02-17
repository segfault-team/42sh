/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcaps_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 21:25:45 by lfabbro           #+#    #+#             */
/*   Updated: 2017/02/17 21:43:47 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Gets terminal name
*/

int			tcaps_get_term_name(char **env)
{
	char	*term;

	if (!(term = ft_getenv(env, "TERM")))
		return (ft_error(SH_NAME, "TERM environment variable is not set", NULL));
	if (tgetent(NULL, ft_strchr(term, '=')) != 1)
		return (ft_error(SH_NAME, "could not find terminfo database", NULL));
	return (0);
}

/*
**	Sets new termios structure
*/

int			tcaps_set(void)
{
	struct termios	tcs;

	if (tcgetattr(STDIN_FILENO, &tcs) < 0)
		return (ft_error(SH_NAME, "could not find termios structure", NULL));
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
	TCAPS.nb_move = 0;
	TCAPS.nb_read = 0;
	TCAPS.check_move = 0;
	TCAPS.hist_move = -1;
	TCAPS.nb_line = 1;
	TCAPS.nb_col = 0;
	// search for term name, if not found is not a big deal
	tcaps_get_term_name(e->env);
	// sets termios structure for the shell. If cannot, it is a deal, so deal it.
	if (tcaps_set())
	{
		//no termios 
		return ;
	}
	xputs("am");
	xputs("bw");
}
