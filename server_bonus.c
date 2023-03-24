/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:19:00 by yokten            #+#    #+#             */
/*   Updated: 2023/03/24 09:10:36 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	convert_char(int data, pid_t *client_pid)
{
	static unsigned char	c;
	static int				i = 7;

	c += data << i;
	if (i == 0)
	{
		i = 7;
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		i--;
	if ((char)c == '\0')
	{
		kill(*client_pid, SIGUSR2);
		*client_pid = 0;
	}
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static pid_t	client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		convert_char(1, &client_pid);
	else if (sig == SIGUSR2)
		convert_char(0, &client_pid);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	pid = getpid();
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd (pid, 1);
	s_sigaction.sa_sigaction = sig_handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &s_sigaction, 0);
	sigaction (SIGUSR2, &s_sigaction, 0);
	while (1)
		pause ();
	return (0);
}
