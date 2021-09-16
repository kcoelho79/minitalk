/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-oliv <kde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:13:35 by kde-oliv          #+#    #+#             */
/*   Updated: 2021/09/16 19:09:44 by kde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

static void	deserialize(int sig, siginfo_t *siginfo, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

 	(void)context;
	if (!client_pid)
		client_pid = siginfo->si_pid;
	// concatena a aplica operador logico or
	// 1 0 = 1
	// 1 1 = 1 
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			// envia sinal para o cliente, fim
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		// envia sinal cliente, completou caracter
		kill(client_pid, SIGUSR1);
	}
	else
	// movimenta o bit para esquerda e acrescentado zero
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = deserialize;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
