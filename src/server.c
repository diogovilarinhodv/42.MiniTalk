#include "minitalk.h"

void	bit_calcs(int signum, int max, unsigned char *ch)
{
	if (signum == SIGUSR1)
		(*ch) |= max;
	else if (signum == SIGUSR2)
		(*ch) ^= max;
}

void	send_signal(int signum, int *max, int *inc, int pid)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		(*max) = ((*max) / 2);
		(*inc)++;
		kill(pid, SIGUSR2);
	}
}

void	byte_completed(int *max, int *inc, unsigned char *ch)
{
	if (*inc == 8)
	{
		if (*ch == 0)
			write(1, "\n", 1);
		else
			write(1, ch, 1);
		*inc = 0;
		*max = 128;
		*ch = 255;
	}
}

void	get_result(int signum, siginfo_t *info, void *context)
{
	static int				inc = 0;
	static unsigned char	ch = 255;
	static int				max = 128;
	static int				client_pid = 0;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	bit_calcs(signum, max, &ch);
	send_signal(signum, &max, &inc, client_pid);
	byte_completed(&max, &inc, &ch);
}

int	main(void)
{
	struct sigaction	sa;
	char				*pid;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_result;
	pid = ft_itoa(getpid());
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	free(pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
