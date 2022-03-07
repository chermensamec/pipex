/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:22 by onelda            #+#    #+#             */
/*   Updated: 2022/03/07 21:01:21 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_script(char *paths[], char *command)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], command);
		free(tmp);
		if (!access(paths[i], X_OK))
			return (paths[i]);
		//free(paths[i]);
		i++;
	}
	return (NULL);
}

char	*get_path(char *envp[], char *command)
{
	char	*path_line;
	char	**paths;
	int		i;

	i = 0;
	path_line = 0;
	printf("11\n");
	while (!path_line)
		path_line = ft_strnstr(*(envp++), "PATH", 5);	
	paths = ft_split(path_line + 5, ':');
	return (find_script(paths, ft_split(command, ' ')[0]));
}
