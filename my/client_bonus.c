/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleyton <nleyton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:57:14 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/23 22:28:15 by nleyton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int  sender(pid_t pid, char c)
{
    int xbit;

    xbit = 128;
    while (xbit > 0)
    {
        g_confirmation = 0;
        if (xbit & c)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        xbit = xbit / 2;
        while(g_confirmation == 0)
            ;
    }
    return(1);
}

static void confirmation(int sig, siginfo_t *siginfo, void *ucontext)
{
    // static int  counter;

    (void)siginfo;
    (void)ucontext;
    if (sig == SIGUSR1)
    {
        g_confirmation = 1;
        // write(1, "Signal ", 7);
        // ft_putnbr_fd(++counter, 1);
        // write(1, " received     \n", 15);
    }
}

int main(int argc, char **argv)
{
    int     i;
    pid_t   pid;
    struct sigaction    action;
    if (argc != 3)
    {
        write(1, "Error: check your arguments and try again!\n", 43);
        return (0);
    }
    action.sa_sigaction = confirmation;
    sigaction(SIGUSR1, &action, NULL);
    // signal(SIGUSR1, &confirmation);
    i = 0;
    pid = (pid_t)ft_atoi(argv[1]);
    while(argv[2][i])
        sender(pid, argv[2][i++]);
    sender(pid, '\0');
    return(1);
}
