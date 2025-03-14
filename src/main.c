/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:40:16 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/14 16:49:43 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	
	(void)ac;
	(void)av;
	minishell_launcher(data);
	return (0);
}
