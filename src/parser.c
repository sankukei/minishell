/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:40:00 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 20:08:20 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	parser(t_data *data, t_cmd **cmd_list)
{
	data->n_commands = 0;
	while (data->token)
	{
		if (!add_cmd_list(data, data->token, cmd_list))
		{
			clear_cmds(cmd_list);
			return ;
		}
		advance_pointer(&data->token);
	}
}
