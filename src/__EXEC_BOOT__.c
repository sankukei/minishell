/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:13:06 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 04:04:22 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*token;
	int	i;

	i = 1;
	token = data->front_token;
	printf("### TOKENS ###\n");
	while (token)
	{
		printf("%d token: %s\ntype: %d\n", i, token->str, token->type);
		i++;
		token = token->next;
	}
	
}

void	print_cmd(t_data *data)
{
	t_cmd	*cmds;
	int	i;
	int	j;

	j = 0;
	i = 0;
	cmds = data->cmd;
	while (cmds)
	{
		printf("PIPELINE %d ###\n", j);
		while (cmds->cmd[i])
		{
			printf("%d cmd: %s\n", i + 1, cmds->cmd[i]);
			i++;
		}
		cmds = cmds->next;
		j++;
	}
}

void	print_redir(t_data *data)
{
	t_redir	*redirsX;
	int	i;

	i = 0;
	redirsX = data->cmd->redirs;
	printf("#### REDIRS ###\n");
	while (redirsX && redirsX->target)
	{
		printf("%d redir: %s\n", i + 1, redirsX->target);
		redirsX =  redirsX->next;
		i++;
	}
}


void	print_stats_of_all_variable(t_data *data)
{
	printf("#### DEBUG ###\n");
	printf("input: %s\n", data->input);
	print_tokens(data);
	print_cmd(data);
	print_redir(data);

}

void	dzero(void *data, unsigned int size)
{
	unsigned int	loop;

	loop = 0;
	while (loop != size)
	{
		(*(char *)&data[loop]) = 0;
		loop += 1;
	}
}

void	minishell_launcher(t_data *data)
{
	char	*input;
	t_cmd		*cmds;
	setup_signals();
	while (1)
	{
		*get_shell_mode() = MODE_MAIN;
		cmds = NULL;
		input = readline("minishell> ");
		if (ft_strlen(input))
		{
			data->input = input;
			data->cmd = cmds;
			add_history(input);
			if (parsing(data))
			{
				prepare_next_input(data, &data->cmd);
				continue ;
			}
			parser(data, &cmds);
			data->cmd = cmds;
			__exec_startup__(data, cmds);
			print_stats_of_all_variable(data);
			prepare_next_input(data, &data->cmd);
		}
		else
			free(input);
	}
}
