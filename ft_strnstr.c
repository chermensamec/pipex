#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	num;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (big[i] && len > i)
	{
		num = 0;
		while (big[i + num] == little[num] && i + num < len)
		{
			num++;
			if (little[num] == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}


