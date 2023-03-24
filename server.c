/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:26:05 by yokten            #+#    #+#             */
/*   Updated: 2023/03/24 03:28:36 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    convert_char(int data)
{
    static char	c;
    static int	i = 7;

	c += data << i;
	if (i == 0)
	{
		i = 7;
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		i--;
}

void    sig_handler(int sig)
{
    if (sig == SIGUSR1)
        convert_char(1);
    else if (sig == SIGUSR2)
        convert_char(0);
}

int main()
{
    int pid;

    pid = getpid();
    ft_putnbr_fd (pid, 1);
    signal (SIGUSR1, sig_handler);
    signal (SIGUSR2, sig_handler);
    while (1)
        pause ();
    return (0);
}