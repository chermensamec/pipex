#include "pipex_bonus.h"

int read_from_terminal(char *limiter)
{
	char *c;
	write(1, "pipe heredoc> ", 14);
	c = 0;
	c = get_next_line(0);
	write(1, c, ft_strlen(c));
	return (0);
}
