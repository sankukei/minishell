/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:17:35 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/22 05:30:41 by amedenec         ###   ########.fr       */
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
		return (fd = 1);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	check_to_close_fd(t_redir *redir, int check)
{
	t_redir	*tmp;

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
		{
			close(fd);
		}
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

	init_t_dup(&dups);
	fd = STDOUT_FILENO;
	while (redir)
	{
		fd = open_fds(redir->target, redir->type);
		if (fd < 0)
		{
			printf("%s : file doesnt exist\n", redir->target);
			handle_file_error(data, vars);
			exit(2);
		}
		fill_t_dups(&dups, redir->type, fd, redir);
		redir = redir->next;
	}
	return (dups);
}

void	handle_dups(t_dup dups, t_data *data)
{
	if (dups.infile_redir)
	{
		if (dups.infile_redir == 3 && dups.infile_fd != 0)
		{
			if (dup2(dups.infile_fd, STDIN_FILENO) == -1)
			{
				clear_cmds(&data->cmd);
				return ;
			}
		}
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
