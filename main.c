/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:17:19 by onelda            #+#    #+#             */
/*   Updated: 2022/03/07 21:10:56 by onelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*paths;
	int 	fd[2];
	char	**tmp;
	int	one, second;
	char *test[3] = {"ls", "-l", NULL};
	pid_t	pid1, pid2;
	pipe(fd);
	one = open("1.txt", O_RDONLY, 0777);
	second = open("2.txt", O_WRONLY | O_RDONLY | O_TRUNC, 0777);
	printf("%d %d\n", fd[0], fd[1]);
	pid1 = fork();
	if (pid1 == 0)
	{
		//dup2(one, STDIN_FILENO);
		//dup2(fd[1], STDOUT_FILENO);
		paths = get_path(envp, argv[2]);
		printf("main %s\n", paths);
		close(fd[0]);
		printf("main %s\n",  ft_split(argv[2], ' ')[0]);
		execve(paths, test, envp);
	}
	/*pid2 = fork();
	if (pid2 == 0)
	{
		paths = get_path(envp, argv[3]);
		dup2(fd[0], STDIN_FILENO);
		dup2(second, STDOUT_FILENO);	
		close(fd[1]);
		//printf("dasda");
		execve(paths, ft_split(argv[3], ' '), envp);
	}*/
	//waitpid(pid1, NULL, 0);
	waitpid(pid1, NULL, 0);
}
