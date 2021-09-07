#include "minitalk.h"

static int	isNegative(int cnt, const char *nptr)
{
	if (*(nptr + cnt) == '-'
		 && ('0' <= *(nptr + (cnt + 1)) && *(nptr + (cnt + 1)) <= '9'))
		return (1);
	return (0);
}

static int	isInvalid(int cnt, const char *nptr)
{
	if ((*(nptr + cnt) == '-' || *(nptr + cnt) == '+')
		 && !('0' <= *(nptr + (cnt + 1)) && *(nptr + (cnt + 1)) <= '9'))
		return (1);
	return (0);
}

static int	isSpecialChar(int cnt, const char *nptr, int foundNum)
{
	if ((*(nptr + cnt) == '+' || *(nptr + cnt) == '-' || (9 <= *(nptr + cnt)
				 && *(nptr + cnt) <= 13) || *(nptr + cnt) == 32)
		 && foundNum == 0)
		return (1);
	return (0);
}

static int	addNumber(int cnt, const char *nptr, int *num)
{
	*num *= 10;
	*num += (*(nptr + cnt) - 48);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	cnt;
	int	foundNum;
	int	isnegative;

	num = 0;
	cnt = 0;
	foundNum = 0;
	isnegative = 0;
	while (*(nptr + cnt) != '\0')
	{
		if (isSpecialChar(cnt, nptr, foundNum) && isInvalid(cnt, nptr))
			return (num);
		else if (isSpecialChar(cnt, nptr, foundNum))
			isnegative = isNegative(cnt, nptr);
		else if ('0' <= *(nptr + cnt) && *(nptr + cnt) <= '9')
			foundNum = addNumber(cnt, nptr, &num);
		else
			break ;
		cnt++;
	}
	if (isnegative == 1)
		num *= (-1);
	return (num);
}