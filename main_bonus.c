#include "pipex_bonus.h"

void	ft_putnbr(int nb)
{
	char	c;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = '0' + nb % 10;
	write(2, &c, 1);
}

void	child_process(char *argv, char **envp, int in_file, int out_file)
{
	char 	*path;
	path = get_path(envp, ft_split(argv, ' '));
	dup2(in_file, STDIN_FILENO);	
	dup2(out_file, STDOUT_FILENO);
	if (path == 0)
		exit (1);		
	ft_putnbr(out_file);
	execve(path, ft_split(argv, ' '), envp);
}

int main(int argc, char **argv, char **envp)
{
	int	*fd;
	int	i;
	char	*path;
	int	fd_file;
	pid_t	pid;

	i = 2;
	fd = malloc(sizeof(int) * (argc - 4) * 2);

	if (!fd)
		return (1);
	if(pipe(fd) == -1)
		exit(1);
	if (argc >= 5)
	{
		if (ft_strnstr(argv[1], "here_doc", 8))
		{
			read_from_terminal(argv[2]);
		}
		while (i != argc - 2)
		{

			fd_file = open(argv[1], O_RDONLY , 0777);
			pid = fork();
			if (pid < 0)
				exit(1);
			if (pid == 0)
			{
				if (i == 2)
					child_process(argv[i], envp, fd_file, *fd);	
				else
					
					child_process(argv[i], envp, *(fd + (i - 2) * 2), *(fd + (i - 2) * 2 + 1));	
			}
				waitpid(pid, NULL, 0);	
			i++;
		}
		pid = fork();

		if (pid == 0)
		{
			fd_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			path = get_path(envp, ft_split(argv[argc - 2], ' '));
			
			ft_putnbr((argc - 4) * 2 - 1);
			dup2(fd[(argc - 4) * 2 - 1], STDIN_FILENO);
			dup2(fd_file, STDOUT_FILENO);
			close(fd[1]);
			execve(path, ft_split(argv[argc - 2], ' '), envp);	
			ft_putnbr(pid);
		}
		close(fd[0]);
		close(fd[1]);
		//close(fd[2]);
		//close(fd[3]);
		write(2, "Hellow_mai4\n", 12);
		waitpid(pid, NULL, 0);
	}
	// читаем get_net_line'ом записываем это в pipe 1 потом делаем этот pipe stdin и дальше как в mandatory и все
}
