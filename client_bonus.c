/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:21:17 by belguabd          #+#    #+#             */
/*   Updated: 2024/01/16 16:35:31 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "minitalk.h"

static void	handle_msg(int sign)
{
	static int	received_flag;

	received_flag = 0;
	if (sign == SIGUSR1)
		received_flag = 1;
	if (received_flag)
		ft_putstr_fd("Message sent successfully\n", 1);
}

static int	validate_input(int ac, char *av[])
{
	if (ac != 3)
	{
		ft_putstr_fd("Invalid input : ./client [server_pid] [message]", 1);
		exit(1);
	}
	if (ft_atoi(av[1]) <= 0)
	{
		ft_putstr_fd("pid incorrect", 1);
		exit(1);
	}
	return (1);
}

static void	__pass(int pid_proc, char c)
{
	int	i;
	int	bit;

	i = 7;
	bit = 0;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		if (bit)
		{
			if (kill(pid_proc, SIGUSR1) < 0)
				exit(1);
		}
		else
		{
			if (kill(pid_proc, SIGUSR2) < 0)
				exit(0);
		}
		usleep(400);
		i--;
	}
}

static int	check_pid(char const *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char *av[])
{
	int	pid_pro;
	int	i;

	signal(SIGUSR1, handle_msg);
	if (validate_input(ac, av) == 1)
	{
		i = 0;
		if (!check_pid(av[1]))
		{
			ft_putstr_fd("pid incorrect", 1);
			exit(1);
		}
		pid_pro = ft_atoi(av[1]);
		while (av[2][i])
		{
			__pass(pid_pro, av[2][i]);
			i++;
		}
		__pass(pid_pro, '\n');
	}
	return (0);
}
