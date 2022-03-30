#include "pipex_bonus.h"

char	**realloc_for_char_arr(char **old, int size)
{
	char **new;
	int	i;
	
	i = 0;
	new = malloc(sizeof(char *) * size + 1);
	if (!new)
		exit (1);

	while (i < size)
	{
		new[i] = old[i];	
		i++;
	}
	return (new);
}

int	write_line(char *limiter, char ***arr, int size)
{
	char *c;
	write(1, "pipe heredoc> ", 14);
	c = 0;
	c = get_next_line(0);
	if (!ft_strncmp(c, limiter, ft_strlen(c) - 1))
		return (1);
	*arr = realloc_for_char_arr(*arr, size);
	(*arr)[size] = c;
	return (0);
}

void read_from_terminal(char *limiter)
{
	int	fd[2];
	int	size;
	char	**arr;
	int 	i;

	i = 0;
	size = 0;
	if (pipe(fd) == -1)
		exit(1);
	while (!write_line(limiter, &arr, size))
		size++;
	while (i < size)
	{
		write(fd[1], arr[i], ft_strlen(arr[i]));
		i++;
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}
