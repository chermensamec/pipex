/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:22 by onelda            #+#    #+#             */
/*   Updated: 2022/03/12 01:59:35 by chermen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*find_script(char *paths[], char *command)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], command);
		free(tmp);
		if (!access(paths[i], X_OK))
		{
			res = ft_strdup(paths[i]);
			return (res);
		}
		i++;
	}
	ft_free_path (paths);
	return (NULL);
}

char	*get_path(char *envp[], char **pars_com)
{
	char	*path_line;
	char	**paths;
	int		i;

	if (!access(pars_com[0], X_OK))
		return (pars_com[0]);
	i = 0;
	path_line = 0;
	while (!path_line)
		path_line = ft_strnstr(*(envp++), "PATH", 5);
	paths = ft_split(path_line + 5, ':');
	return (find_script(paths, pars_com[0]));
}
