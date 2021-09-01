#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "ft_atoi.c"
#include "ft_strdup.c"

void    send_bin(char ch, int server_pid)
{
	int	num;
	int	max;

	num = (int) ch;
	max = 128;
	while(max > 0)
	{
		if (num >= max)
		{
			num -= max;
			kill(server_pid, SIGUSR1);
		}
		else
			kill(server_pid, SIGUSR2);
		max /= 2;
		usleep(25);
	}
}

int main(int argc, char **argv)
{
    int     server_pid;
    char    *str;
    int     inc;

    server_pid = ft_atoi(argv[argc - 2]);
    str = ft_strdup(argv[argc - 1]);
    inc = 0;
    while (*(str + inc) != '\0')
    {
        send_bin(*(str + inc), server_pid);
        inc++;
    }
	free(str);
    kill(server_pid, SIGTERM);
    return (0);
}