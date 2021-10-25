/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleyton <nleyton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:45:55 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/23 22:30:55 by nleyton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk_bonus.h"

static void    receive_and_print(int sig, siginfo_t *siginfo, void *ucontext)
{
    static int  c;
    static int  xbit;
    static pid_t    client_pid;

    if (client_pid == 0)
        client_pid = siginfo->si_pid;
    (void)ucontext;
    if(!xbit)
        xbit = 128;
    if (sig == SIGUSR1)
        c = c + xbit;
    xbit = xbit / 2;
    if (xbit == 0)
    {
        if (c == '\0')
        {
            client_pid = 0;
            write(1, "\n", 1);
        }
        else
            write(1, &c, 1);
        c = 0;
    }
    kill(client_pid, SIGUSR1);
}

int main(void)
{
    pid_t               pid;
    struct sigaction    action;

    pid = getpid();
    write(1, "PID: ", 4);
    ft_putnbr_fd((int)pid, 1);
    write(1, "\n", 1);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = receive_and_print;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        pause();
    return(1);
}
