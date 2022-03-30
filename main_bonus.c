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

void child_process(char *argv, char **envp)
{

	int	fd[2];
	pid_t	pid;
	int	status;
	if (pipe(fd) == -1)
		exit(1);
	pid = fork();	
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);	
		close(fd[0]);
		execve(get_path(envp, ft_split(argv, ' ')), ft_split(argv, ' '), envp);
		write(2, "Eror execve\n", 12);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

int main(int argc, char **argv, char **envp)
{
	int fd_file[2];
	int i;

	i = 2;
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		read_from_terminal(argv[2]);	
		i = 3;
	}
	else 
	{
		fd_file[0] = open(argv[1], O_RDONLY, 0644);
		dup2(fd_file[0], STDIN_FILENO);
	}
	while (i != argc - 2)
		child_process(argv[i++], envp);	
	fd_file[1] = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd_file[1], STDOUT_FILENO);
	execve(get_path(envp, ft_split(argv[i], ' ')), ft_split(argv[i], ' '), envp);
	close(fd_file[0]);
	close(fd_file[1]);
}
