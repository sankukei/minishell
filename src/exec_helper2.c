/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:57 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/02 03:48:56 by amedenec         ###   ########.fr       */
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
	vars->cmd = 0;
	vars->heredoc_index = 0;
	vars->current_pipe_index = 0;
}

int	init_pipes(t_exec *vars)
{
	int	i;
	int	n;

	i = 0;
	n = vars->n_command;
	if (n == 1 || n == 0)
	{
		vars->pipes = 0;
		return (1);
	}
	vars->pipes = malloc((n -1) * sizeof(int *));
	if (!vars->pipes)
		return (1);
	n--;
	while (n--)
	{
		vars->pipes[i] = malloc(sizeof(int) * 2);
		if (!vars->pipes[i])
			return (1);
		pipe(vars->pipes[i]);
		i++;
	}
	return (0);
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

void	wait_all_childrens(t_data *data, t_exec *vars)
{
	while (wait(&vars->status) > 0)
		data->last_exit_status = WEXITSTATUS(vars->status);
}

void	restore_fds(t_exec *vars)
{
	dup2(vars->old_stdout, STDOUT_FILENO);
}
