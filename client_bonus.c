/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:28:24 by yokten            #+#    #+#             */
/*   Updated: 2023/03/24 09:23:56 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	show_error(int err)
{
	if (err == 0)
		ft_putstr_fd("You must enter valid PID", 1);
	else if (err == 1)
		ft_putstr_fd("You must enter valid string", 1);
	else if (err == 2)
		ft_putstr_fd("Something happened, couldn't send the data", 1);
	else if (err == 3)
		ft_putstr_fd("Wrong PID format", 1);
	else if (err == 4)
		ft_putstr_fd("You can send one string", 1);
	exit(1);
}

void	send(int pid, int ch)
{
	unsigned char	c;
	int				i;

	i = 128;
	c = ch;
	while (i > 0)
	{
		if (i <= c)
		{
			if (kill(pid, SIGUSR1) == -1)
				show_error(2);
			c -= i;
		}
		else
			if (kill(pid, SIGUSR2) == -1)
				show_error(2);
		i /= 2;
		usleep(100);
	}
}

void	received(int a)
{
	static int	flag = 1;

	if (a == SIGUSR2 && flag == 1)
	{
		ft_putstr_fd("Message sent succesfully!", 1);
		flag = 0;
	}
}

int	main(int ac, char **av)
{
	if (!av[1])
		show_error(0);
	else if (!av[2])
		show_error(1);
	else if (ac == 3)
	{
		int	pid;
		char	*str;
		int		i;

		i = 0;
		signal (SIGUSR2, received);
		pid = ft_atoi(av[1]);
		while (av[1][i])
		{
			if (av[1][i] < '0' || av[1][i] > '9')
				show_error(3);
			i++;
		}
		i = 0;
		str = av[2];
		while (str[i])
			send(pid, str[i++]);
	}
}
