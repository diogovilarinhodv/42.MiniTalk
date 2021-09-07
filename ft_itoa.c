#include "minitalk.h"

static int	n_count(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static int	n_mult(int amount)
{
	int	cnt;

	cnt = 1;
	while (amount > 0)
	{
		cnt *= 10;
		amount--;
	}
	return (cnt);
}

static void	p_input(char *p, int n, int neg)
{
	int	inc_p;
	int	amount;

	amount = n_count(n);
	inc_p = 0;
	if (neg == 1 && n != 0)
	{
		p[inc_p] = '-';
		inc_p++;
	}
	if (n == 0)
	{
		*(p + inc_p) = n + '0';
		inc_p++;
	}
	else
	{
		while (amount > 0)
		{
			*(p + inc_p) = (n / n_mult(amount - 1)) + '0';
			n %= n_mult(amount - 1);
			inc_p++;
			amount--;
		}
	}
}

static void	is_max_neg_int(int neg_max_int, char *p, int n, int neg)
{
	if (neg_max_int)
	{
		p[n_count(n)] = (p[n_count(n)] + 1);
		p[n_count(n) + 1] = '\0';
	}
	else if (neg == 1)
		p[n_count(n) + 1] = '\0';
	else
		p[n_count(n)] = '\0';
}

char	*ft_itoa(int n)
{
	char	*p;
	int		neg;
	int		neg_max_int;

	neg_max_int = 0;
	neg = 0;
	if (n < 0)
		neg = 1;
	if (neg)
	{
		if (n == -2147483648)
		{
			n += 1;
			neg_max_int = 1;
		}
		n *= (-1);
	}
	p = (char *) malloc(sizeof(char) * (neg + n_count(n) + 1));
	if (p == NULL)
		return (NULL);
	p_input(p, n, neg);
	is_max_neg_int(neg_max_int, p, n, neg);
	return (p);
}