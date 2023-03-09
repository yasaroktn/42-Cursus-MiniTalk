#ifndef MINITALK_H
#define MINITALK_H
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int     ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strchr(const char *s, int c);

#endif 