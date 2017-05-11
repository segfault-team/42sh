/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:07:20 by lfabbro           #+#    #+#             */
/*   Updated: 2017/05/03 16:07:22 by kboddez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_sigcheck(int sig)
{
	if (sig == SIGINT)
		return (ft_error(NULL, "Interrupted", NULL));
	else if (sig == SIGILL)
		return (ft_error(NULL, "Illegal istruction", NULL));
	else if (sig == SIGTRAP)
		return (ft_error(NULL, "Trace trap", NULL));
	else if (sig == SIGABRT)
		return (ft_error(NULL, "Aborted", NULL));
	else if (sig == SIGFPE)
		return (ft_error(NULL, "Floating point exception", NULL));
	else if (sig == SIGKILL)
		return (ft_error(NULL, "Killed", NULL));
	else if (sig == SIGBUS)
		return (ft_error(NULL, "Bus error", NULL));
	else if (sig == SIGSEGV)
		return (ft_error(NULL, "Segmentation fault", NULL));
	else if (sig == SIGSYS)
		return (ft_error(NULL, "Non existent system call", NULL));
	else if (sig == SIGPIPE)
		return (ft_error(NULL, "Broken pipe", NULL));
	else if (sig == SIGTERM)
		return (ft_error(NULL, "Software termination", NULL));
	else if (sig == SIGSTOP || sig == SIGTSTP)
		return (ft_error(NULL, "Stopped", NULL));
	return (0);
}

int			ft_handle_ret_signal(int status)
{
	int			sig;
	int			i;
	char		*uknw_sig;

	if (!WIFEXITED(status) && WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		i = -1;
		while (++i <= 13)
			if (ft_sigcheck(sig))
				return (-1);
		uknw_sig = ft_itoa(sig);
		ft_error("Process terminated with unknown signal", uknw_sig, NULL);
		strfree(&uknw_sig);
		return (-1);
	}
	return (0);
}

/*
** Since we may have errors we don't ignore ctrl-z signal for now
*/

void		ft_set_sig_handler(void)
{
	int		sig;

	sig = 0;
	while (++sig <= 31)
	{
		if (sig == SIGSTOP || sig == SIGSEGV || sig == SIGKILL
				|| sig == SIGBUS || sig == SIGFPE)
			signal(sig, SIG_DFL);
		else
			signal(sig, ft_sig_handler);
	}
}

void		ft_sig_handler(int sig)
{
	t_env *e;

	e = env_access(NULL);
	if (sig == SIGINT)
		ft_sigint(e);
	else if (sig == SIGTSTP)
	{
		tcaps_ctrl_end(e);
		tcaps_reset(e);
		signal(sig, SIG_DFL);
		ioctl(0, TIOCSTI, e->susp);
	}
	else if (sig == SIGCONT)
	{
		if (!e->raw)
		{
			ft_prompt(e->prompt);
			ft_putstr(e->line);
		}
		tcsetattr(STDIN_FILENO, TCSANOW, e->new_term);
		signal(SIGTSTP, ft_sig_handler);
	}
	else if (sig == SIGWINCH)
		tcaps_recalc_pos(e);
}
