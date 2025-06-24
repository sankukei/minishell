/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:49:26 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/24 14:49:27 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void	exec_single_builtin_new(void)
{
	
}

int	detect_fd_flag(char *fd_name, int type)
{
	int	fd;

	if (type == 4)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
	}
	else if (type == 2)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (0);
	}
	return (fd);
}

void	handle_redir(t_redir *redir)
{
	int	fd;
	while (redir)
	{
		fd = detect_fd_flag(redir->target, redir->type);
		if (redir->next && redir->type == 4 && redir->type == 2)
			close(fd);
		redir = redir->next;
	}
	redir->fd = fd;
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands)
{	
	if (!(check_if_builtin(commands->cmd[0]) && commands->redirs))
		return (1);
	handle_redir(commands->redirs);
	exec_builtin(check_if_builtin(commands->cmd[0]), cmd, fd); // il faut passer data a cette fonction -_-
	return (0);
}

void	children_exec_new(t_exec *vars)
{
	
}

void	start_children_new(t_exec *vars)
{
	int	i;

	i = 0;
	while (i < vars->n_command)
	{
		vars->pid = fork();
		if (vars->pid == 0)
			children_exec_new(vars);
			
	}
}

int	__exec_startup_new__(t_data *data)
{
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	commands = data->cmd;
	//check_for_heredoc(commands);
	vars->n_command = get_number_of_commands(data->token);
	if (vars->n_command == 1)
		if (handle_single_builtin_new(vars, commands))
			return (1);
	init_pipes(vars);
	start_children_new(vars);
	return (0);
}
