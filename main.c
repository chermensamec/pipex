/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:19 by onelda            #+#    #+#             */
/*   Updated: 2022/03/12 02:04:16 by chermen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char *path, char **pars_com)
{
	int	i;

	i = 0;
	free(path);
	while (pars_com[i])
		free(pars_com[i++]);
	free(pars_com);
}

void	ft_error(int err_num)
{
	if (err_num == 0)
	{
		perror("command not found");
		exit(127);
	}
	else if (err_num == 1)
	{
		perror("Erorr open");
		exit(1);
	}	
	else if (err_num == 2)
		perror("Erorr when make pipe");
	else if (err_num == 3)
		perror("Erorr fork");
	else if (err_num == 4)
	{
		write(2, "Erorr: Nothing turn in\n", 23);
		exit(1);
	}
	exit(errno);
}

int	child_process1(char *file, int *fd, char *envp[], char *command)
{
	int		fd_file;
	char	*path;
	char	**pars_com;

	fd_file = open(file, O_RDONLY, 0777);
	if (fd_file == -1)
		ft_error(1);
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	pars_com = ft_split(command, ' ');
	path = get_path(envp, pars_com);
	execve(path, pars_com, envp);
	free_paths(path, pars_com);
	close(fd[1]);
	ft_error(0);
}

int	child_process2(char *file, int *fd, char *envp[], char *command)
{
	int		fd_file;
	char	*path;
	char	**pars_com;

	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file < 0)
		ft_error(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	close(fd[1]);
	pars_com = ft_split(command, ' ');
	path = get_path(envp, pars_com);
	execve(path, pars_com, envp);
	free_paths(path, pars_com);
	close(fd[1]);
	ft_error(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		status[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error(2);
		pid1 = fork();
		if (pid1 < 0)
			ft_error(3);
		if (pid1 == 0)
			ft_error(child_process1(argv[1], fd, envp, argv[2]));
		pid2 = fork();
		if (pid2 < 0)
			ft_error(3);
		if (pid2 == 0)
			ft_error(child_process2(argv[4], fd, envp, argv[3]));
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, &status[0], 0);
		waitpid(pid2, &status[1], 0);
		if (WIFEXITED(status[1]) != 0)
			return (WEXITSTATUS(status[1]));
		if (WIFEXITED(status[0]) != 0)
			return (WEXITSTATUS(status[0]));
	}
	else
		ft_error(4);
}
