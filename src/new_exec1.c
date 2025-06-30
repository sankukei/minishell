/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:49:26 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 04:57:27 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	exec_single_builtin_new(void)
{
	
}

int	open_fds(char *fd_name, int type)
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
	else if (type == 3)
	{
		fd = open(fd_name, O_RDONLY, 0644);
		if (fd < 0)
			return (0);
	}
	else if (type == 1)
	{
		fd = open(".heredoc_buffer", O_RDONLY, 0644);
		if (fd < 0)
			return (0);
	}
	return (fd);
}

int	handle_redir(t_redir *redir)
{
	int	fd;

	fd = 1;
	if (!redir)
		return (1);
	while (redir)
	{
		printf("reddir detected\n");
		fd = open_fds(redir->target, redir->type);
		redir->fd = fd;
		if (redir->next && redir->type == 4 && redir->type == 2 && redir->type == 3)
			close(fd);
		redir = redir->next;
	}
	return (fd);
}

void	handle_dups(int fd, int type)
{
	if (type == 3)
		dup2(fd, STDIN_FILENO);
	else if (type == 4)
		dup2(fd, STDOUT_FILENO);
	else if (type == 2)
		dup2(fd, STDOUT_FILENO);
	//else if (type == 1)
	//	dup2(fd, STDOUT_FILENO);
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{	
	int	fd;

	(void)vars;
	fd = 1;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (0);
	fd = handle_redir(commands->redirs);
	// fd = commands->redirs->fd;
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, fd); // il faut passer data a cette fonction -_-
	return (1);
}

void	children_exec_new(t_exec *vars, t_data *data, int i, t_cmd *cmds)
{
    int	fd = 1;

    if (cmds->redirs)
    {
        fd = handle_redir(cmds->redirs);
        handle_dups(fd, cmds->redirs->type);
    }
    if (!(setup_output_pipes(vars, i)) || !(setup_input_pipes(vars, i)))
    {
        free_exec(vars);
        exit(1);
    }
    close_unused_pipes(data, vars, i);

    if (check_if_builtin(cmds->cmd[0]))
        exec_builtin(check_if_builtin(cmds->cmd[0]), cmds->cmd, data, fd);
    else if (!(exec_single(data, cmds->cmd[0], cmds->cmd)))
    {
        printf("execve failed\n");
        free_exec(vars);
		clear_cmds(&data->cmd);
        exit(1);
    }
    exit(0);
}

void	start_children_new(t_exec *vars, t_data *data, t_cmd *cmds)
{
	int	i;
	t_cmd	*commands;
	
	commands = cmds;	
	i = 0;
	*get_shell_mode() = MODE_CHILD;
	while (i < vars->n_command && commands && commands->cmd)
	{
		vars->pid = fork();
		if (vars->pid == 0)
			children_exec_new(vars, data, i, commands);
		i++;
		commands = commands->next;
	}
}
int	get_n_command_new(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds->cmd)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);	

}
// CHECK LE RETURN DU MALLOC
int	__exec_startup__(t_data *data, t_cmd *cmds)
{
	//il faut preparer le nouvel input et free tout ce merdier entre chaque call
	//fix le fd dans single_builtin, mettre cmds->redir->fd a la place	
	// creer la liste de cmd si le parser trouve une pipe
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	if (!vars)
		return (1);
	bzero(vars, sizeof(t_exec));
	commands = data->cmd;
	check_for_heredoc(commands);
	vars->n_command = data->n_commands;
	printf("TRUE n_command %d\n", vars->n_command);
	if (vars->n_command == 1)
		if (handle_single_builtin_new(vars, commands, data))
			return (1);
	init_pipes(vars);
	start_children_new(vars, data, cmds);
	close_pipes(vars);
	wait_all_childrens(vars);
	restore_fds(vars);
	free_exec(vars);
	return (0);
}
