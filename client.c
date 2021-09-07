#include "minitalk.h"

void    send_bin(unsigned char ch, int server_pid, int max, int inc)
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

int main(int argc, char **argv)
{
	int		server_pid;
	char	*str;
	int		inc;

	inc = 0;
	server_pid = ft_atoi(argv[argc - 2]);
	str = ft_strdup(argv[argc - 1]);
	if (argc != 3)
	{
		write(1,"Error Input!\n", 13);
		return (0);
	}
	while (*(str + inc) != '\0')
	{
		send_bin(*(str + inc), server_pid, 128, 8);
		inc++;
	}
	send_bin(*(str + inc), server_pid, 128, 8);
	free(str);
	return (0);
} 