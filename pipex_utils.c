#include "pipex.h"

char	**get_paths(char *envp[], char *comand)
{
	char	*path_line;
	char	**paths;
	char	*tmp;
	int	i;

	i = 0;
	path_line = 0;
	while (!path_line)
		path_line = ft_strnstr(*(envp++), "PATH", 5);
	paths = ft_split(path_line + 5, ':');
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);	
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], comand);	
		free(tmp);	
		i++;
	}
	return (paths);
}
