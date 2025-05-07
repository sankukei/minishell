/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:18:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/05/07 14:03:48 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clear_struct(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->str);
		free(*tokens);
		*tokens = tmp;
	}
}

void	clear_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}


void	prepare_next_input(t_data *data)
{
	clear_struct(&data->token);
}

void	exit_program(t_data *data)
{
	clear_struct(&data->token);
	clear_double_array(data->env);
	free(data);
	exit(1);
}
