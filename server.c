#include "minitalk.h"

void get_result(int signum)
{
	static int				inc = 0;
	static unsigned char	ch = 255;
	static int				max = 128;

	if (signum == SIGUSR1)
		ch |= max;
	else if (signum == SIGUSR2)
		ch ^= max;
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		max /= 2;
		inc++;
	}
	if (inc == 8)
	{
		if (ch == 0)
			write(1, "\n", 1);
		else
			write(1, &ch, 1);
		inc = 0;
		max = 128;
		ch = 255;
	}
}

int main(int argc, char **argv)
{
	char *pid;

	pid = ft_itoa(getpid());
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	free(pid);
	signal(SIGUSR1, get_result);
	signal(SIGUSR2, get_result);
	while(1)
		pause();
    return (0);
}