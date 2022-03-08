/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:19 by onelda            #+#    #+#             */
/*   Updated: 2022/03/08 23:06:16 by chermen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "pipex.h"

void child_process1(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_RDONLY, 0777);
	if(fd_file < 0)
		return ;
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	path = get_path(envp, command);	
	printf("%s\n", path);
	close(fd[0]);
	if (execve(path, ft_split(command, ' '), envp) == -1)
		exit(1);
}

void child_process2(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd_file < 0)
		exit(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	path = get_path(envp, command);
	close(fd[1]);	
	printf("%s\n", path);
	if(execve(path, ft_split(command, ' '), envp) == -1)
		exit(1);
}
int main(int argc, char *argv[], char *envp[])
{
	int 	fd[2];
	pid_t	pid1;
	pid_t	pid2;
	printf("%d\n", getpid());
	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1  < 0)
		exit(1);
	if (pid1 == 0)
	{
		printf("if1 %d\n", getpid());
		child_process1(argv[1], fd, envp, argv[2]);		
		exit(1);
	}
	else 
	{
		printf("else1 %d\n", getpid());
		printf("%d\n", getpid());
		waitpid(pid1, NULL, 0);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit(1);
	if (pid2 == 0)	
	{
		printf("if2 %d\n", getpid());
		child_process2(argv[4], fd, envp, argv[3]);
		exit(1);
	}
	else 
	{
		printf("else2 %d\n", getpid());
		printf("%d\n", getpid());
		//waitpid(pid2, NULL, 0);	
	}
}
