/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:04:03 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/14 03:57:43 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	minishell_launcher(t_data *data)
{
	//char	*input;

	//while (1)
	//{
		//input = readline("minishell> ");
		//if (!input)
		//{
		//	printf("exit\n");
		//	exit(0);
		//}
		parsing(data);
	//	printf("%s", input);
	//	free(input);		
	//}
}