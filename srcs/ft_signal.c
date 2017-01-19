/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:31:41 by lfabbro           #+#    #+#             */
/*   Updated: 2016/12/06 17:31:43 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
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
		{
			if (ft_sigcheck(sig))
			{
				return (-1);
			}
		}
		uknw_sig = ft_itoa(sig);
		ft_error("Process terminated with unknown signal:", uknw_sig, NULL);
		free(uknw_sig);
		return (-1);
	}
	return (0);
}

void		ft_set_sig_handler(void)
{
	int		sig;

	sig = 0;
	while (++sig < 31)
	{
		if (sig == SIGSTOP || sig == SIGCONT || sig == SIGSEGV || \
			sig == SIGKILL || sig == SIGBUS || sig == SIGFPE || sig == SIGTSTP)
			signal(sig, SIG_DFL);
		else
			signal(sig, ft_sig_handler);
	}
}

void		ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		ft_putstr("$> ");
	}
}
