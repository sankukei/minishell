/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:17:35 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 20:18:12 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	open_fds(char *fd_name, int type)
{
	int	fd;

	fd = 1;
	if (type == TRUNC)
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
	else if (type == INPUT)
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

void	fill_t_dups(t_dup *dups, int type, int fd)
{
	if (type == INPUT)
	{
		dups->infile_fd = fd;
		dups->infile_redir = type;
	}
	else if (type == APPEND)
	{
		dups->outfile_fd = fd;
		dups->outfile_redir = type;
	}
	else if (type == TRUNC)
	{
		dups->outfile_fd = fd;
		dups->outfile_redir = type;
	}
}

t_dup	handle_redir(t_redir *redir)
{
	int		fd;
	t_dup	dups;

	dups.infile_fd = 0;
	dups.outfile_fd = 0;
	dups.infile_redir = 0;
	dups.outfile_redir = 0;
	fd = 1;
	while (redir)
	{
		printf("reddir detected\n");
		fd = open_fds(redir->target, redir->type);
		if (redir->next && redir->type != 1)
			close(fd);
		fill_t_dups(&dups, redir->type, fd);
		redir = redir->next;
	}
	return (dups);
}

void	handle_dups(t_dup dups)
{
	if (dups.infile_redir)
	{
		if (dups.infile_redir == 3)
			dup2(dups.infile_fd, STDIN_FILENO);
	}
	if (dups.outfile_redir)
	{
		printf("%d\n", dups.outfile_redir);
		if (dups.outfile_redir == 2)
			dup2(dups.outfile_fd, STDOUT_FILENO);
		else if (dups.outfile_redir == 4)
			dup2(dups.outfile_fd, STDOUT_FILENO);
	}
}

int	handle_single_builtin_new(t_exec *vars, t_cmd *commands, t_data *data)
{
	int		fd;
	t_dup	dups;

	(void)vars;
	fd = 1;
	if (!(check_if_builtin(commands->cmd[0]) && commands && commands->cmd))
		return (0);
	dups = handle_redir(commands->redirs);
	exec_builtin(check_if_builtin(commands->cmd[0]), commands->cmd, data, dups);
	free(vars);
	return (1);
}
