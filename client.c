/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:27:22 by ebansse           #+#    #+#             */
/*   Updated: 2025/03/14 15:48:44 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_flag;

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = -1;
	while (++bit < 8)
	{
		if ((c >> (7 - bit)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_flag == 0)
			usleep(50);
		g_flag = 0;
	}
}

void	rep_serv(int signal)
{
	if (signal == SIGUSR1)
		g_flag = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("message received by server\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (kill(pid, 0) != 0)
		{
			ft_printf("Invalid PID\n");
			exit(1);
		}
		i = -1;
		signal(SIGUSR1, rep_serv);
		signal(SIGUSR2, rep_serv);
		while (argv[2][++i])
			send_char(pid, argv[2][i]);
		send_char(pid, '\0');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		exit(1);
	}
	return (0);
}
