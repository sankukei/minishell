/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:40:16 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/30 06:24:33 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	bzero(data, sizeof(t_data));
	(void)ac;
	(void)av;
	init(data, envp);
	init_terminal();
	minishell_launcher(data);
	return (0);
}
