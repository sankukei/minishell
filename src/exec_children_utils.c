/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:47:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/17 11:47:47 by leothoma         ###   ########.fr       */
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
	printf("coucou\n");
	if (vars->is_heredoc)
	{
		printf("c) fd -> %d\n", vars->heredoc_fd);
		if (dup2(vars->heredoc_fd, STDIN_FILENO) == - 1)
			write(1, "dup2 failed\n", 13);
		//rediriger le stdin de la commande qui contient le heredoc par le fd dans lequel on write la data du heredoc
		vars->is_heredoc = 0;
		close(vars->heredoc_fd);
	}
	else if (i != 0)
	{
		printf("yo les mais\n");
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
