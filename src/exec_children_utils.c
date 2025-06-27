/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <leothoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:47:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 20:54:30 by leothoma         ###   ########.fr       */
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
	if (i != 0)
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

void	close_unused_pipes(t_data *data, t_exec *vars, int i)
{
    int j;
    int n = data->n_commands - 1;

    if (!vars->pipes) // Ajout de ce check
        return;

    for (j = 0; j < n; j++)
    {
        if (j != i - 1)
            close(vars->pipes[j][0]);
        if (j != i)
            close(vars->pipes[j][1]);
    }
}
