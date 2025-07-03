/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:49:39 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 23:50:13 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*token;
	int		i;

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
	int		i;
	int		j;

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
	t_redir	*redirs_x;
	int		i;

	i = 0;
	redirs_x = data->cmd->redirs;
	printf("#### REDIRS ###\n");
	while (redirs_x && redirs_x->target)
	{
		printf("%d redir: %s\n", i + 1, redirs_x->target);
		redirs_x = redirs_x->next;
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
