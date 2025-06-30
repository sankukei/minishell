/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 04:16:05 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/30 04:57:49 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


t_mode *get_shell_mode(void)
{
    static t_mode mode = MODE_MAIN;
    return &mode;
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
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (mode == MODE_HEREDOC)
		{
			write(1, "\n", 1);
		}
		else if (mode == MODE_CHILD)
			write(1, "\n", 1);


	}
	else if (signum == SIGQUIT && mode == MODE_CHILD)
        write(1, "Quit (core dumped)\n", 19);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}