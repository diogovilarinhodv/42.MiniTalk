#include "minitalk.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		cnt;

	p = (char *)malloc(ft_strlen(s) + 1);
	cnt = 0;
	if (p == NULL)
		return (NULL);
	while (*(s + cnt) != '\0')
	{
		*(p + cnt) = *(s + cnt);
		cnt++;
	}
	*(p + cnt) = '\0';
	return (p);
}
