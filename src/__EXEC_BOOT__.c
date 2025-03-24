/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_BOOT__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/20 03:58:39 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data)
{
	char	*input;

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
		printf("%s\n", data->input);
	}
}
