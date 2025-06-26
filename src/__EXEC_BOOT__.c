/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:13:06 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/25 22:48:33 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data)
{
	char	*input;
	t_cmd		*cmds;

	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (ft_strlen(input))
		{
			data->input = input;
			add_history(input);
			cmds = (t_cmd *)malloc(sizeof(t_cmd));
			if (parsing(data))
			{
	//			prepare_next_input(data, &cmds);
				continue ;
			}
			parser(data, cmds);
			data->cmd = cmds;
			__exec_startup__(data, cmds);
	//		prepare_next_input(data, &data->cmd);
		}
	}
}
