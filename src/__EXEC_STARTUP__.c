/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/24 03:18:39 by amedenec         ###   ########.fr       */
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

int	check_if_redir(t_cmd *commands)
{
	return (commands->redirs);
	// while (token && token->type != PIPE)
	// {
	// 	if (token->type == 2
	// 		|| token->type == 3 || token->type == 4)
	// 		return (token->type);
	// 	token = token->next;
	// }	
	// return (0);
}

void	handle_redir(t_redir *redir)
{
	
	while (redir)
	{
		detect_fd_flag()
		redir = redir->next;
	}
}
int	detect_fd_flag(char *fd_name, int type, t_exec *vars)
{
	int	fd;

	if (type == 4)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	else if (type == 3)
	{
		fd = open(fd_name, O_RDONLY);
		if (fd < 0)
			exit(1);
		else
			dup2(fd, 0);
	}
	else if (type == 2)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(1);
		else
			dup2(fd, 1);
	}
	return (fd);
}

int	handle_single_builtin(t_exec *vars, t_cmd *commands)
{	
	if (!(check_if_builtin(commands->cmd[0] && commands->redirs)))
		return (1);
	handle_redir(commands->redirs);
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
	if (vars->n_command == 1)
		if (handle_single_builtin(vars, commands))
			return (1);
	return (0);
}


/*int	new_exec_startup(t_data *data){

	vars = malloc(sizeof(t_exec));
	init_exec_variables(vars);
}*/
