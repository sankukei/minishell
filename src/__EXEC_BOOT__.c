/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:13:06 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 07:05:38 by amedenec         ###   ########.fr       */
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

	i = 0;
	cmds = data->cmd;
	printf("#### CMD (one pipe) ###\n");
	while (cmds->cmd[i])
	{
		printf("%d cmd: %s\n", i + 1, cmds->cmd[i]);
		i++;
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

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	dzero(cmds, sizeof(t_cmd));
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		//printf("HAA\n");
		if (ft_strlen(input))
		{
			data->input = input;
			add_history(input);
			if (parsing(data))
			{
				prepare_next_input(data, &cmds);
				continue ;
			}
			parser(data, &cmds);
			data->cmd = cmds;
			//printf("%x\n", cmds->redirs);
			__exec_startup__(data, cmds);
			print_stats_of_all_variable(data);
			prepare_next_input(data, &data->cmd);
		}
	}
}
