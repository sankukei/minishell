#include "../headers/minishell.h"

int	main(int ac, char **av)
{
	(void)ac;
	write (1, "minishell> ", 11);
	while (1)
	{
		printf("%s", readline(av[1]));		
	}
	return (0);
}
