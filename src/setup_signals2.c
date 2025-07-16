
#include "../headers/minishell.h"


void	handle_sigint_exit(void)
{
	t_data **data = get_data_ctx(NULL);

	if (data)
		(*data)->last_exit_status = 130;
}

void	handle_sigint(int signum)
{
	t_mode	mode;

	mode = *get_shell_mode();
	handle_sigint_exit();
	if (signum == SIGINT)
	{
		if (mode == MODE_MAIN)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			ioctl(STDIN_FILENO, TIOCSTI, "\0");
			// rl_redisplay();
		}
		else if (mode == MODE_HEREDOC)
		{
			// voir sigint_heredoc_handler
			return ;
		}
		else if (mode == MODE_CHILD)
		{
			write(1, "\n", 1);
		}
	}
}


void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	update_sigquit(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (*get_shell_mode() == MODE_MAIN)
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = handle_sigquit;

	sigaction(SIGQUIT, &sa, NULL);
}


t_data *get_data_ctx(t_data *new_data)
{
	static t_data *ctx = NULL;

	if (new_data != NULL)
		ctx = new_data;
	return (ctx);
}