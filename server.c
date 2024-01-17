/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:50:30 by belguabd          #+#    #+#             */
/*   Updated: 2024/01/16 15:55:32 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "minitalk.h"

static void	handle_msg(int sing, siginfo_t *info, void *content)
{
	static int	pid_proc;
	static int	b;
	static int	c;

	(void)content;
	if (pid_proc == 0)
		pid_proc = info->si_pid;
	if (pid_proc != info->si_pid)
	{
		b = 0;
		c = 0;
		pid_proc = 0;
	}
	if (sing == SIGUSR1)
		c += 1 << (7 - b);
	else
		c += 0 << (7 - b);
	b++;
	if (b == 8)
	{
		ft_putchar_fd(c, 1);
		b = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	sa.sa_sigaction = handle_msg;
	sa.sa_flags = SA_SIGINFO;
	server_pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
