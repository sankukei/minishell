/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:10:20 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/18 03:36:42 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*temp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		temp = (*cmds)->next;
		clear_cmd_node(*cmds);
		*cmds = temp;
	}
}

void	prepare_next_input(t_data *data, t_cmd **cmds)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->front_token)
	{
		clear_struct(&data->front_token);
		data->front_token = NULL;
	}
	clear_struct(&data->front_token);
	if (cmds && *cmds)
	{
		clear_cmds(cmds);
		*cmds = NULL;
	}
}

void	exit_program(t_data *data, char **args)
{
	int	exit_tmp;

	exit_tmp = data->last_exit_status;
	free(data->input);
	clear_struct(&data->front_token);
	clear_double_array(data->env);
	if (args && args[1])
	{
		exit_tmp = ft_atoi(args[1]);
		clear_cmds(&data->cmd);
		exit(exit_tmp);
	}
	else
	{
		clear_cmds(&data->cmd);
		exit(exit_tmp);
	}
}
