#include "minitalk.h"

void	get_result(int signum)
{
	static unsigned char	c = 255;
	static int				ascii_n = 0;

	if (signum == SIGUSR1)
		c ^= 128 >> ascii_n;
	else if (signum == SIGUSR2)
		c |= 128 >> ascii_n;
	ascii_n++;
	if (ascii_n == 8)
	{
		write(1, &c,1);
		ascii_n = 0;
		if (c == 0)
		{
			ft_putstr_fd("\n", 1);
		}
		c = 255;
	}
}

int 	main(int argc, char **argv)
{
	char *pid;

	pid = ft_itoa(((int)getpid()));
	write(1, pid, ft_strlen(pid));
	signal(SIGUSR1, get_result);
	signal(SIGUSR2, get_result);
	while(1)
		pause();
	return (0);
}