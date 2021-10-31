/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzianis <dzianis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:57:14 by nleyton           #+#    #+#             */
/*   Updated: 2021/10/28 05:02:59 by dzianis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	sender(pid_t pid, char c)
{
	int	xbit;

	xbit = 128;
	while (xbit > 0)
	{
		g_confirmation = 0;
		if ((xbit & c) == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		xbit = xbit / 2;
		while (g_confirmation == 0)
			;
	}
	return (1);
}

static void	confirmation(int sig)
{
	if (sig == SIGUSR1)
	{
		g_confirmation = 1;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "Error: check your arguments and try again!\n", 43);
		return (0);
	}
	signal(SIGUSR1, &confirmation);
	i = 0;
	pid = (pid_t)ft_atoi(argv[1]);
	while (argv[2][i])
		sender(pid, argv[2][i++]);
	sender(pid, '\0');
	return (1);
}
