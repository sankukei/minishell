#include "../headers/minishell.h"
int	main(int ac, char **av)
{
	char	*input;
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			return (0);
		}
		printf("%s\n", input);
		free(input);		
	}
	return (0);
}
