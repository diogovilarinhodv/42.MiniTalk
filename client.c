#include "minitalk.h"

void	send_bin(int server_pid, char *str)
{
	int		inc;
	int		ascii_n;

	inc = 0;
	while(*(str + inc) != '\0')
	{
		ascii_n = 0;
		while (ascii_n < 8)
		{
			if (*(str + inc) & 128 >> ascii_n)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			ascii_n++;
			usleep(25);
		}
		inc++;
	}
}

int		main(int argc, char **argv)
{
	int		server_pid;
	char	*str;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[argc - 2]);
	str = ft_strdup(argv[argc - 1]);
	send_bin(server_pid, str);
	free(str);
	return (0);
}