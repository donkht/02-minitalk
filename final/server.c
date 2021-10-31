/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzianis <dzianis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:45:55 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/28 05:10:11 by dzianis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	receive_and_print(int sig, siginfo_t *siginfo, void *ucontext)
{
	static int		c;
	static int		xbit;
	static pid_t	client_pid;

	if (client_pid == 0 && ((void)ucontext))
		client_pid = siginfo->si_pid;
	if (!xbit)
		xbit = 128;
	if (sig == SIGUSR1)
		c = c + xbit;
	xbit = xbit / 2;
	if (xbit == 0)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			client_pid = 0;
			kill(siginfo->si_pid, SIGUSR1);
			return ;
		}
		else
			write(1, &c, 1);
		c = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	write(1, "PID: ", 4);
	ft_putnbr_fd((int)pid, 1);
	write(1, "\n", 1);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = receive_and_print;
	sigaction(SIGUSR2, &action, 0);
	sigaction(SIGUSR1, &action, 0);
	while (1)
		;
	return (1);
}
