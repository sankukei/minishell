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

#include "../headers/minishell.h"

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

	if (!redir)
		return ;
	while (redir)
	{
		fd = detect_fd_flag(redir->target, redir->type);
		if (redir->next && redir->type == 4 && redir->type == 2)
			close(fd);
		redir = redir->next;
	}
	redir->fd = fd;
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{	
	int	fd;

	fd = 1;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (1);
	printf("yoo\n");
	fflush(stdout);
	handle_redir(commands->redirs);
	if (commands->redirs)
		fd = commands->redirs->fd;
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, fd); // il faut passer data a cette fonction -_-
	return (1);
}

void	children_exec_new(t_exec *vars)
{
	
	printf("dans children_exec\n");
	exit(1);
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
		i++;
	}
}

int	__exec_startup__(t_data *data, t_cmd *cmds)
{
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	commands = cmds;
	//check_for_heredoc(commands);
	vars->n_command = get_number_of_commands(data->token);
	if (vars->n_command == 1)
		if (handle_single_builtin_new(vars, commands, data))
			return (1);
	init_pipes(vars);
	start_children_new(vars);
	close_pipes(vars);
	wait_all_childrens(vars);
	restore_fds(vars);
	return (0);
}
