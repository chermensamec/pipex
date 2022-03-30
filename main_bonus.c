#include "pipex_bonus.h"

void ft_error_bonus(int i)
{
	if (i == 0)
		return ;
	else if (i == 1)
		perror("Erorr when make pipe");
	else if (i == 2)
		perror("Erorr fork");
	else if (i == 3)
	{
		perror("command not found");
		exit(127);
	}
	else if (i == 4)
	{
		write(2, "Wrong number of argements\n", 26);
		exit(1);
	}
	else if (i == 5)
	{
		perror("Erorr open");
		exit(1);
	}
	else
		exit(i);
	exit(errno);
}

int	child_process(char *argv, char **envp)
{

	int	fd[2];
	pid_t	pid;
	int	status;
	if (pipe(fd) == -1)
		return (1);
	pid = fork();	
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);	
		dup2(fd[1], STDOUT_FILENO);		
		close(fd[1]);	
		execve(get_path(envp, ft_split(argv, ' ')), ft_split(argv, ' '), envp);
		return (3);
	}
	close(fd[1]);	
	dup2(fd[0], STDIN_FILENO);	
	close(fd[0]);
	waitpid(pid, &status, 0);	
	if (WIFEXITED(status) != 0)
		return (WEXITSTATUS(status));
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int fd_file[2];
	int i;
	int error_status;
	
	if (argc < 5)
		ft_error_bonus(4);
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		read_from_terminal(argv[2]);	
		i = 3;
	}
	else 
	{
		i = 2;
		fd_file[0] = open(argv[1], O_RDONLY, 0777);	
		if (fd_file[0] < 0)
			ft_error_bonus(5);
		dup2(fd_file[0], STDIN_FILENO);		
		close(fd_file[0]);
	}
	while (i != argc - 2)
		ft_error_bonus(child_process(argv[i++], envp));
	fd_file[1] = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_file[1] < 0)
			ft_error_bonus(5);
	dup2(fd_file[1], STDOUT_FILENO);
	close(fd_file[1]);
	execve(get_path(envp, ft_split(argv[i], ' ')), ft_split(argv[i], ' '), envp);
	ft_error_bonus(3);
}
