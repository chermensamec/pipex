#include "pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		read_from_terminal(argv[2]);
	}
	// читаем get_net_line'ом записываем это в pipe 1 потом делаем этот pipe stdin и дальше как в mandatory и все
}	
