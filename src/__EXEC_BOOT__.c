/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/04 01:55:20 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


void	minishell_launcher(t_data *data)
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
			if (0 == strcmp(data->token->str, "exit"))
				exit_program(data);
			//__exec_startup__(data);
			//printf("%s\n", data->input);
			prepare_next_input(data);
		}
	}
}
