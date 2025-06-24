/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/23 23:33:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	__exec_startup__(t_data *data)
{
	t_exec	*vars;

	vars = malloc(sizeof(t_exec));
	init_exec_variables(vars);
	check_for_heredoc(data->token, vars);
	vars->n_command = get_number_of_commands(data->token);
	if (vars->n_command > 100)
		return (printf("too many commands\n"));
	if (handle_single_builtin(vars, data))
		return (1);
	init_pipes(vars);
	start_children(vars, data);
	close_pipes(vars);
	wait_all_childrens(vars);
	restore_fds(vars);
	return (0);
}

int	__exec_startup__(t_data *data)
{
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	commands = data->cmd;
	//check_for_heredoc(commands);
	vars->n_command = get_number_of_commands(data->token);
	return (0);
}


/*int	new_exec_startup(t_data *data){

	vars = malloc(sizeof(t_exec));
	init_exec_variables(vars);
}*/
