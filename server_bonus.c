/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzianis <dzianis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:45:55 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/15 19:52:02 by dzianis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk_bonus.h"

static void    receive_and_print(int sig, siginfo_t *siginfo, void *ucontext)
{
    static int  c;
    static int  xbit;

    (void)ucontext;
    kill(siginfo->si_pid, SIGUSR1);
    if(!xbit)
        xbit = 128;
    if (sig == SIGUSR1)
        c = c + xbit;
    xbit = xbit / 2;
    if (xbit == 0)
    {
        if (c == '\0')
            write(1, "\n", 1);
        else
            write(1, &c, 1);
        c = 0;
    }
}

int main()
{
    pid_t               pid;
    struct sigaction    action;

    pid = getpid();
    write(1, "PID:", 4);
    ft_putnbr_fd((int)pid, 1)
    write(1, "\n", 1);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = receive_and_print;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        pause();
    return(1);
}