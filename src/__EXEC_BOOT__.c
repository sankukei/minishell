/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/05/05 06:05:29 by amedenec         ###   ########.fr       */
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
			if (!input)
			{
				printf("exit\n");
				exit(0);
			}
			add_history(input);
			parsing(data);
			//__EXEC_STARTUP__(data);
			if (0 == strcmp(data->token->str, "exit"))
				exit_program(data);
			//printf("%s\n", data->input);
			prepare_next_input(data);
		}
	}
}
