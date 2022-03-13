/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:12:07 by onelda            #+#    #+#             */
/*   Updated: 2022/03/13 18:38:01 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_line(int fd, char *buff, char *remainder)
{
	int		bytes_r;
	char	*tmp;

	bytes_r = 1;
	if (!remainder)
		remainder = ft_strdup("");
	if (!remainder)
		return (0);
	while (!ft_strchr(remainder, '\n') && bytes_r)
	{
		bytes_r = read(fd, buff, 1);
		if (bytes_r < 0)
		{
			free(remainder);
			return (0);
		}
		buff[bytes_r] = '\0';
		tmp = remainder;
		remainder = ft_strjoin(remainder, buff);
		free(tmp);
		if (!remainder)
			return (0);
	}	
	return (remainder);
}

char	*ft_get_remaind(char *remainder)
{
	char	*res;
	int		i;

	i = 0;
	if (!remainder)
		return (0);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\0')
	{
		free(remainder);
		return (0);
	}
	res = (char *) malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));
	if (!res)
	{
		free(remainder);
		return (0);
	}
	ft_strlcpy(res, remainder + i + 1, ft_strlen(remainder) - i + 1);
	free(remainder);
	return (res);
}

char	*ft_cut_line(char	*remainder)
{
	char	*res;
	int		i;

	i = 0;
	if (!remainder)
		return (0);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	res = malloc(sizeof(char) * (i + 2));
	if (!res)
		return (0);
	ft_strlcpy(res, remainder, i + 2);
	if (!res[0])
	{
		free(res);
		return (0);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*remainder;
	char		*res;

	if (fd < 0)
		return (0);
	buff = (char *) malloc (sizeof(char) * (2));
	if (!buff)
		return (0);
	remainder = get_line(fd, buff, remainder);
	free (buff);
	res = ft_cut_line(remainder);
	remainder = ft_get_remaind(remainder);
	return (res);
}
