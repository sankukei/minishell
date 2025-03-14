/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/14 16:53:26 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		parsing(data, input);
	//	printf("%s\n", input);
		free(input);		
	}
}
