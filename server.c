#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	bin_number[8];

void	reset_bin_number()
{
	int	inc;

	inc = 0;
	while(inc < 8)
	{
		bin_number[inc] = -1;
		inc++;
	}
}

int	full_filled()
{
	int	inc;
	int	who_many_nbrs;

	inc = 0;
	who_many_nbrs = 0;
	while(inc < 8)
	{
		if (bin_number[inc] == 0 || bin_number[inc] == 1)
			who_many_nbrs++;
		inc++;
	}
	if (who_many_nbrs == 8)
		return (1);
	return (0);
}

void	set_bin_numbers(int sig_value)
{
	int		inc;
	int		total;
	char	*ch;
	int		max;

	inc = 0;
	total = 0;
	max = 128;
	while(inc < 8)
	{
		if (bin_number[inc] == -1)
		{
			bin_number[inc] = sig_value;
			inc++;
			break;
		}
		inc++;
	}
	if (inc == 8)
	{
		inc = 0;
		while(inc < 8)
		{
			if (bin_number[inc] == 1)
				total += max;
			max /= 2;
			inc++;
		}
		ch = malloc(1);
		*ch = (char) total;
		write(1, ch, 1);
		free(ch);
	}
}

void get_result(int signum)
{
	if (full_filled() == 1)
		reset_bin_number();
	if (signum == SIGUSR1)
		set_bin_numbers(1);
	else if (signum == SIGUSR2)
		set_bin_numbers(0);
}


int main(int argc, char **argv)
{
    int pid;

	pid = getpid();
	reset_bin_number();
	printf("%d\n", pid);
	signal(SIGUSR1, get_result);
	signal(SIGUSR2, get_result);
	while(1)
		pause();
    return (0);
}
