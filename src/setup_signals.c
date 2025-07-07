/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:16:05 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/30 06:38:08 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

int	*get_sigint_flag(void)
{
	volatile static int	sigint_received = 0;

	return (&sigint_received);
}

t_mode	*get_shell_mode(void)
{
	static t_mode	mode;

	mode = MODE_MAIN;
	return (&mode);
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	*get_sigint_flag() = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigquit(int signum)
{
	t_mode	mode;

	mode = *get_shell_mode();
	if (signum == SIGQUIT)
	{
		if (mode == MODE_CHILD)
			write(1, "Quit (core dumped)\n", 19);
	}
}

void	handle_sigint(int signum)
{
	t_mode	mode;

	mode = *get_shell_mode();
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
