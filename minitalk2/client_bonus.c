/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzianis <dzianis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:57:14 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/23 01:37:25 by dzianis          ###   ########.fr       */
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
        pause();
        while(!g_confirmation)
            ;
    }
    return(1);
}

static void confirmation(int sig)
{
    // static int  counter;

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
    char*   str;

    if (argc != 3)
    {
        write(1, "Error: check you arguments and try again!\n", 21);
        return (0);
    }
    signal(SIGUSR1, &confirmation);
    i = 0;
    pid = (pid_t)ft_atoi(argv[1]);
    str = argv[2];
    while(str[i])
        sender(pid, str[i++]);
    sender(pid, '\0');
    return(1);
}
