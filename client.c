/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-oliv <kde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:31:15 by kde-oliv          #+#    #+#             */
/*   Updated: 2021/09/16 19:10:07 by kde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

static void	success(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
	{
		++received;
	}
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	send_signal(int pid, int sig)
{
	int		signal;

	if (sig == 1)
		signal = SIGUSR2;
	if (sig == 0)
		signal = SIGUSR1;
	if (kill(pid, signal))
	{
		ft_putstr_fd("Error, Do you start Server or PID is correct  ?", 1);
		exit(EXIT_FAILURE);
	}
}

static void	serialize(int pid, char *str)
{
	int		bit;
	char	c;

	while (*str)
	{
		bit = 8;
		c = *str++;
		while (bit--)
		{
			if (c >> bit & 1)
				send_signal(pid, 1);
			else
				send_signal(pid, 0);
			usleep(100);
		}
	}
	bit = 8;
	while (bit--)
	{
		usleep(100);
		send_signal(pid, 0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;
	int					pid;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr_fd("input error missing args \n", 1);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	s_sigaction.sa_handler = success;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	serialize(pid, argv[2]);
	while (1)
		pause();
		// pausa até receber um sinal
	return (0);
}
