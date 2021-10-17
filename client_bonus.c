#include "minitalk_bonus.h"

static int  sender(pid_t pid, char c)
{
    int xbit;

    xbit = 128;
    while (xbit > 0)
    {
        if (xbit & c)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        xbit = xbit / 2;
        usleep(100);
    }
    return(1);
}

static void confirmation(int sig)
{
    static int  counter;

    counter++;
    write(1, "Signal", 6);
    ft_putnbr_fd(counter, 1);
    write(1, "received\n", 9);
}

int main(int argc, char **argv)
{
    int     i;
    pid_t   pid;
    char*   str;

    signal(SIGUSR1, &confirmation);
    i = 0;
    pid = (pid_t)ft_atoi(argv[1]);
    str = argv[2];
    while(str[i])
        sender(pid, str[i++]);
    sender(pid, '\0');
    return(1);
}