#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*res;

	res = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, s, ft_strlen(s) + 1);
	return (res);
}
