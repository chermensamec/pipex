/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:05:13 by onelda            #+#    #+#             */
/*   Updated: 2022/03/12 15:05:14 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
