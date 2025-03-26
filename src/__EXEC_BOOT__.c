/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/26 06:36:51 by amedenec         ###   ########.fr       */
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
		data->input = input;
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		// split_tokens(data);
		parsing(data);
		if (0 == strcmp(data->token->str, "exit"))
			exit_program(data);
		printf("%s\n", data->input);
		prepare_next_input(data);
	}
}
