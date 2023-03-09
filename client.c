#include "minitalk.h"

void	send(int pid, int ch)
{
	char	c = ch;
	int		i = 128;
	while(i > 0)
	{
		if(i <= c)
		{
			kill(pid, SIGUSR1);
			c -= i;
		}
		else
			kill(pid, SIGUSR2);
		i /= 2;
		usleep(100);
	}
}


int main(int ac, char **av)
{
	if(ac == 3)
	{
		int pid;
		char *str;
		int i = 0;

		pid = ft_atoi(av[1]);
		str = av[2];
		while(str[i])
			send(pid, str[i++]);
	}
}