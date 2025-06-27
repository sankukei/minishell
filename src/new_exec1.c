/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:49:26 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 04:04:18 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exec_single_builtin_new(void)
{
	
}

int	detect_fd_flag(char *fd_name, int type)
{
	int	fd;

	fd = 1;
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

	fd = 1;
	if (!redir)
		return ;
	while (redir)
	{
		printf("reddir detected\n");
		fflush(stdout);
		fd = detect_fd_flag(redir->target, redir->type);
		if (redir->next && redir->type == 4 && redir->type == 2)
			close(fd);
		redir = redir->next;
	}
	//redir->fd = fd;
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{	
	int	fd;

	fd = 1;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (0);
	handle_redir(commands->redirs);
	if (commands->redirs)
		fd = commands->redirs->fd;
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, fd); // il faut passer data a cette fonction -_-
	return (1);
}

void	children_exec_new(t_exec *vars, t_data *data, int i, t_cmd *cmds)
{
	int	fd;

	fd = 1;
	handle_redir(cmds->redirs);
	if (cmds->redirs)
		fd = cmds->redirs->fd;
	if (!(setup_output_pipes(vars, i)) || !(setup_input_pipes(vars, i)))
	{
		free_exec(vars);
		exit(1);
	}
	if (check_if_builtin(cmds->cmd[0]))
		exec_builtin(check_if_builtin(cmds->cmd[0]), cmds->cmd, data, fd);
	else if (!(exec_single(data, cmds->cmd[0], cmds->cmd)))
	{
		printf("execve failed\n");
		free_exec(vars);
		exit(1);
	}
	exit(0);
}

void	start_children_new(t_exec *vars, t_data *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < vars->n_command)
	{
		vars->pid = fork();
		if (vars->pid == 0)
			children_exec_new(vars, data, i, cmds);
		i++;
	}
}

int	__exec_startup__(t_data *data, t_cmd *cmds)
{
	//il faut preparer le nouvel input et free tout ce merdier entre chaque call
	//fix le fd dans single_builtin, mettre cmds->redir->fd a la place	
	// creer la liste de cmd si le parser trouve une pipe
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	commands = data->cmd;
	//check_for_heredoc(commands);
	vars->n_command = get_number_of_commands(data->token);
	if (vars->n_command == 1)
		if (handle_single_builtin_new(vars, commands, data))
			return (1);
	init_pipes(vars);
	start_children_new(vars, data, cmds);
	close_pipes(vars);
	wait_all_childrens(vars);
	restore_fds(vars);
	free(vars);
	return (0);
}
