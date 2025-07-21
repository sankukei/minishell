/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:17:35 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/18 03:36:46 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	open_fds(char *fd_name, int type)
{
	int	fd;

	if (type == TRUNC)
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == 2)
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == INPUT)
		fd = open(fd_name, O_RDONLY, 0644);
	else
		fd = open(".heredoc_buffer", O_RDONLY, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	check_to_close_fd(t_redir *redir, int check)
{
	t_redir *tmp;

	tmp = redir;
	if (!tmp->next)
		return (0);
	tmp = tmp->next;
	while (tmp)
	{
		if (check == 1 && tmp->type == INPUT)
			return (1);
		if (check == 2 && (tmp->type == APPEND || tmp->type == TRUNC))
			return (1);
		tmp = tmp->next;
	}
	return (0);

}
void	fill_t_dups(t_dup *dups, int type, int fd, t_redir *redir)
{
	if (type == INPUT)
	{
		dups->infile_fd = fd;
		if (check_to_close_fd(redir, 1))
			close(fd);
		dups->infile_redir = type;
	}
	else if (type == APPEND)
	{
		dups->outfile_fd = fd;
		if (check_to_close_fd(redir, 2))
			close(fd);
		dups->outfile_redir = type;
	}
	else if (type == TRUNC)
	{
		dups->outfile_fd = fd;
		if (check_to_close_fd(redir, 2))
			close(fd);
		dups->outfile_redir = type;
	}
}

t_dup	handle_redir(t_data *data, t_redir *redir, t_exec *vars)
{
	int		fd;
	t_dup	dups;

	dups.infile_fd = 0;
	dups.outfile_fd = 0;
	dups.infile_redir = 0;
	dups.outfile_redir = 0;
	fd = STDOUT_FILENO;
	while (redir)
	{
		fd = open_fds(redir->target, redir->type);
		if (fd < 0)
		{
			printf("file doesnt exist\n");
			clear_cmds(&data->cmd);
			exit_child_process(data);
			exit(2);
		}
		fill_t_dups(&dups, redir->type, fd, redir);
		redir = redir->next;
	}
	return (dups);
}

void	handle_dups(t_dup dups)
{
	if (dups.infile_redir)
	{
		if (dups.infile_redir == 3 && dups.infile_fd != 0)
			dup2(dups.infile_fd, STDIN_FILENO);
		close(dups.infile_fd);
	}
	if (dups.outfile_redir)
	{
		if (dups.outfile_redir == 2)
			dup2(dups.outfile_fd, STDOUT_FILENO);
		else if (dups.outfile_redir == 4)
			dup2(dups.outfile_fd, STDOUT_FILENO);
		close(dups.outfile_fd);
	}
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{
	t_dup	dups;

	(void)vars;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (0);
	dups = handle_redir(data, commands->redirs, vars);
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, dups);
	return (1);
}
