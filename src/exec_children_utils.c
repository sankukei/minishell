/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:47:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/21 09:10:57 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_exec(t_exec *vars)
{
	int	a;

	a = 0;
}

int	setup_output_pipes(t_exec *vars, int i)
{
	if (i != vars->n_command - 1)
	{
		close(vars->pipes[i][0]);
		if (dup2(vars->pipes[i][1], STDOUT_FILENO) == -1)
		{
			write(1, "dup2 failed\n", 13);
			return (0);
		}
		close(vars->pipes[i][1]);
	}
	return (1);
}

int	setup_input_pipes(t_exec *vars, int i)
{
	if (vars->is_heredoc && vars->current_pipe_index == vars->heredoc_index)
	{
		close(vars->heredoc_fd);
		if (vars->pipes)
			close(vars->pipes[i - 1][1]);
		int fdd = open(".heredoc_buffer", O_RDONLY);
		if (fdd < 0)
		{
			write(2, "open failed\n", 13);
			perror("open .heredoc_buffer");
		}
		if (dup2(fdd, STDIN_FILENO) == - 1)
		{
			write(2, "dup2 failed\n", 13);
			close(fdd);
			return (0);
		}
		//rediriger le stdin de la commande qui contient le heredoc par le fd dans lequel on write la data du heredoc
		close(fdd);
		vars->is_heredoc = 0;
		// if (vars->pipes)
		// 	close(vars->pipes[i - 1][0]);
	}
	else if (i != 0)
	{
		close(vars->pipes[i - 1][1]);
		if (dup2(vars->pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			write(1, "dup2 failed\n", 13);
			return (0);
		}
		close(vars->pipes[i - 1][0]);
	}
	return (1);
}
