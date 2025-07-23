/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:49:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/23 13:49:56 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	init_t_dup(t_dup *dups)
{
	dups->infile_fd = 0;
	dups->outfile_fd = 0;
	dups->infile_redir = 0;
	dups->outfile_redir = 0;
}

void	handle_file_error(t_data *data, t_exec *vars)
{
	int	i;

	i = -1;
	while (++i < vars->n_command - 1)
	{
		close(vars->pipes[i][1]);
		close(vars->pipes[i][0]);
	}
	clear_cmds(&data->cmd);
	clear_double_array(data->env);
	exit_child_process(data, data->bool_for_free_env);
	free_exec(data->vars);
}
