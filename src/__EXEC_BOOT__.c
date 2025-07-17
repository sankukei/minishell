/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:13:06 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/16 15:22:01 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	handle_ctrl_d(void)
{
	write(1, "exit\n", 5);
	unlink(".heredoc_buffer");
	exit(0);
}

static void	handle_input(t_data *data, char *input, t_cmd *cmds)
{
	data->input = input;
	data->cmd = cmds;
	add_history(input);
	if (parsing(data))
	{
		prepare_next_input(data, &data->cmd);
		return ;
	}
	parser(data, &cmds);
	data->cmd = cmds;
	__exec_startup__(data, cmds);
	prepare_next_input(data, &data->cmd);
}

void	minishell_launcher(t_data *data)
{
	char	*input;
	t_cmd	*cmds;

	setup_signals();
	while (1)
	{
		*get_shell_mode() = MODE_MAIN;
		update_sigquit();
		*get_sigint_flag() = 0;
		cmds = NULL;
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell> ");
		if (!input)
			handle_ctrl_d();
		if (ft_strlen(input))
		{
			handle_input(data, input, cmds);
		}
		else
			free(input);
	}
}
