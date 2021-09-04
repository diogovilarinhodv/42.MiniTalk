#ifndef MINITALK_H
#define MINITALK_H

	#include <unistd.h>
	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>

	char	*ft_strdup(const char *s);
	size_t 	ft_strlen(const char *s);
	int		ft_atoi(const char *nptr);
	char	*ft_itoa(int n);

	void	ft_putstr_fd(char *s, int fd);
	void	ft_putchar_fd(char c, int fd);
	void	ft_putnbr_fd(int n, int fd);

#endif