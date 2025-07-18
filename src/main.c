/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:40:16 by amedenec          #+#    #+#             */
/*   Updated: 2025/07/18 03:37:05 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		data;

	(void)ac;
	(void)av;
	init(&data, envp);
	get_data_ctx(&data);
	init_terminal();
	minishell_launcher(&data);
	return (0);
}
