/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/14 03:55:12 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"


void	parsing(t_data	*data)
{
	//printf("%d\n", add_token(&data->token, "coucou", 5));
	data->token->str = "coucou";
	printf("%s\n", data->token->str);
}
