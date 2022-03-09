/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:19 by onelda            #+#    #+#             */
/*   Updated: 2022/03/09 16:10:26 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int err_num)
{
	if (err_num == 0)
		perror("Wrong arguments: ");
	else if (err_num == 1)
		perror("Erorr open: ");	
	else if (err_num == 2)	
		perror("Erorr when make pipe");	
	else if (err_num == 3)
		perror("Erorr fork: ");	
		exit(1);
}

void child_process1(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_RDONLY, 0777);
	if(fd_file < 0)
		return (1);
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	path = get_path(envp, command);	
	//close(fd[0]);
	if (execve(path, ft_split(command, ' '), envp) == -1)
		return (0);
}

int	child_process2(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd_file < 0)
		return (1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	path = get_path(envp, command);
	//close(fd[1]);	
	if(execve(path, ft_split(command, ' '), envp) == -1)
		return (0);
}
int	main(int argc, char *argv[], char *envp[])
{
	int 	fd[2];
	pid_t	pid1;
	pid_t	pid2;
	
	if (pipe(fd) == -1)
		ft_exit(2);
	pid1 = fork();
	if (pid1  < 0)
		ft_exit(3);
	if (pid1 == 0)
		ft_exit(child_process1(argv[1], fd, envp, argv[2]));		
	else 
	waitpid(pid1, NULL, 0);
	close(fd[1]);
	pid2 = fork();
	if (pid2 < 0)
		ft_exit(3);
	if (pid2 == 0)	
		ft_exit(child_process2(argv[4], fd, envp, argv[3]));
	waitpid(pid2, NULL, 0);	
	close(fd[0]);
}
