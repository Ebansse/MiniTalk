/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:34:03 by ebansse           #+#    #+#             */
/*   Updated: 2025/03/27 14:22:48 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static char		c;
	static int		bit;
	static pid_t	pid_client;

	(void)context;
	if (info->si_pid != 0)
		pid_client = info->si_pid;
	if (signal == SIGUSR1)
		c |= (0b10000000 >> bit);
	else if (signal == SIGUSR2)
		c &= ~(0b10000000 >> bit);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(pid_client, SIGUSR2);
			return ;
		}
		write(1, &c, 1);
	}
	kill(pid_client, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
