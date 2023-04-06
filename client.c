/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:25:49 by yokten            #+#    #+#             */
/*   Updated: 2023/04/06 22:15:38 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	char	c;
	int		i;

	c = ch;
	i = 128;
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

int	main(int ac, char **av)
{
	char	*str;
	int		pid;
	int		i;

	if (!av[1])
		show_error(0);
	else if (!av[2])
		show_error(1);
	else if (ac == 3)
	{
		i = 0;
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
