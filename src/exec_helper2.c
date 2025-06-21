/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:57 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/21 09:19:24 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_exec_variables(t_exec *vars)
{
	vars->old_stdin = dup(STDIN_FILENO);
	vars->old_stdout = dup(STDOUT_FILENO);
	vars->fd = 1;
	vars->is_reddir = 0;
	vars->n_command = 0;
	vars->is_builtin = 0;
	vars->is_heredoc = 0;
	vars->cmd = 0;
	vars->heredoc_index = 0;
	vars->current_pipe_index = 0;
}

void	init_pipes(t_exec *vars)
{
	int	i;
	int	n;

	i = 0;
	n = vars->n_command;
	if (n == 1 || n == 0)
	{
		vars->pipes = 0;
		return ;
	}
	vars->pipes = malloc(n * sizeof(int *));
	n--;
	while (n--)
	{
		vars->pipes[i] = malloc(sizeof(int) * 2);
		pipe(vars->pipes[i]);
		i++;
	}
}

void	close_pipes(t_exec *vars)
{
	int	i;

	i = 0;
	while (i < vars->n_command - 1)
	{
		close(vars->pipes[i][0]);
		close(vars->pipes[i][1]);
		i++;
	}
}

void	wait_all_childrens(t_exec *vars)
{
	while (wait(&vars->status) > 0)
		;
}

void	restore_fds(t_exec *vars)
{
	if (vars->is_heredoc)
		close(vars->heredoc_fd);
	close(vars->old_stdin);
	dup2(vars->old_stdout, STDOUT_FILENO);
	close(vars->old_stdout);
}
