/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:40:16 by amedenec          #+#    #+#             */
/*   Updated: 2025/04/25 23:02:06 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	t_cmd		*cmds;
	//t_redir		*redir_list;

	data = (t_data *)malloc(sizeof(t_data));
	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	if (!data)
		return (1);
	if (!cmds)
		return (1);
	(void)ac;
	(void)av;
	init(data, envp);
	minishell_launcher(data, cmds);
	return (0);
}
