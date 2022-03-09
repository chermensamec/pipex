#include "pipex.h"

void child_process1(char *file, int *fd, char *envp[], char *command)
{
    int fd_file;
    char    *path;

    fd_file = open(file, O_RDONLY, 0777);
    if(fd_file < 0)
        return ;
    dup2(fd_file, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    path = get_path(envp, command);
    //close(fd[0]);
    if (execve(path, ft_split(command, ' '), envp) == -1)
        exit(1);
}

void child_process2(char *file, int *fd, char *envp[], char *command)
{
    int fd_file;
    char    *path;

    fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if(fd_file < 0)
        exit(1);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd_file, STDOUT_FILENO);
    path = get_path(envp, command);
    //close(fd[1]);
    if(execve(path, ft_split(command, ' '), envp) == -1)
        exit(1);
}
int main(int argc, char *argv[], char *envp[])
{
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (pipe(fd) == -1)
}
mi-u3% cd projects/pipex
mi-u3% vim main.c
mi-u3% cat main.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:19 by onelda            #+#    #+#             */
/*   Updated: 2022/03/09 15:38:05 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_process(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_RDONLY, 0777);
	if(fd_file < 0)
		return ;
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	path = get_path(envp, command);
	if (execve(path, ft_split(command, ' '), envp) == -1)
		exit(1);
}

void last_child_process(char *file, int *fd, char *envp[], char *command)
{
	int	fd_file;
	char	*path;

	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd_file < 0)
		exit(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_file, STDOUT_FILENO);
	path = get_path(envp, command);
	//close(fd[1]);
	if(execve(path, ft_split(command, ' '), envp) == -1)
		exit(1);
}
int main(int argc, char *argv[], char *envp[])
{
	int 	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1  < 0)
		exit(1);
	if (pid1 == 0)
	{
		child_process1(argv[1], fd, envp, argv[2]);
		ft_exit(1);
	}
	else
	waitpid(pid1, NULL, 0);
	close(fd[1]);
	pid2 = fork();
	if (pid2 < 0)
		ft_exit(1);
	if (pid2 == 0)
	{
		child_process2(argv[4], fd, envp, argv[3]);
		ft_exit(1);
	}
	waitpid(pid2, NULL, 0);
	close(fd[0]);
}
