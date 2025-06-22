/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/04 23:51:32 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data, t_cmd *cmd)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (ft_strlen(input))
		{
			data->input = input;
			add_history(input);
			if (parsing(data))
			{
				prepare_next_input(data);
				continue ;
			}
			parser(data, cmd);
			__exec_startup__(data);
			prepare_next_input(data);
		}
	}
}
