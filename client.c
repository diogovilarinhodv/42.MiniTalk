#include "minitalk.h"

void	sig_confirm(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		write(1, "Signal sended\n", 14);
}

void	send_bin(unsigned char ch, int server_pid, int max, int inc)
{
	if (ch >= max && ch != 0)
	{
		ch -= max;
		kill(server_pid, SIGUSR1);
	}
	else
		kill(server_pid, SIGUSR2);
	usleep(125);
	if (inc > 1)
		send_bin(ch, server_pid, (max / 2), (inc - 1));
}

int	main(int argc, char **argv)
{
	int					server_pid;
	char				*str;
	int					inc;
	struct sigaction	sa;

	inc = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_confirm;
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		write(1, "Error Input!\n", 13);
		return (0);
	}
	server_pid = ft_atoi(argv[argc - 2]);
	str = ft_strdup(argv[argc - 1]);
	while (*(str + inc) != '\0')
	{
		send_bin(*(str + inc), server_pid, 128, 8);
		inc++;
	}
	if (ft_strlen(str) > 0)
		send_bin(*(str + inc), server_pid, 128, 8);
	free(str);
	return (0);
}
