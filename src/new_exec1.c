/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:49:26 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 20:18:10 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	children_exec_new(t_exec *vars, t_data *data, int i, t_cmd *cmds)
{
	t_dup	dups;

	ft_bzero(&dups, sizeof(dups));
	if (!(setup_output_pipes(vars, i)) || !(setup_input_pipes(vars, i)))
	{
		clear_cmds(&data->cmd);
		free_exec(vars);
		exit(1);
	}
	if (cmds->redirs)
	{
		dups = handle_redir(cmds->redirs);
		handle_dups(dups);
	}
	close_unused_pipes(data, vars, i);
	if (check_if_builtin(cmds->cmd[0]))
	{
		exec_builtin(check_if_builtin(cmds->cmd[0]), cmds->cmd, data, dups);
		int	i = 0;

		while (i < vars->n_command - 1)
			free(vars->pipes[i++]);
		free(vars->pipes);
		free(vars);
	//	free_exec(vars);
	}
	else if (!(exec_single(data, cmds->cmd[0], cmds->cmd)))
	{
		printf("execve failed\n");
		free_exec(vars);
		clear_cmds(&data->cmd);
		exit(127);
	}
	clear_double_array(data->env);
	exit(0);
}

void	start_children_new(t_exec *vars, t_data *data, t_cmd *cmds)
{
	int		i;
	t_cmd	*commands;

	commands = cmds;
	i = 0;
	*get_shell_mode() = MODE_CHILD;
	while (i < vars->n_command && commands && commands->cmd)
	{
		vars->pid = fork();
		if (vars->pid == 0)
		{
			children_exec_new(vars, data, i, commands);
		}
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

int	__exec_startup__(t_data *data, t_cmd *cmds)
{
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	if (!vars)
		return (1);
	bzero(vars, sizeof(t_exec));
	vars->heredoc = 0;
	commands = data->cmd;
	check_for_heredoc(vars, commands);
	vars->n_command = data->n_commands;
	if (vars->n_command > 100)
		return (printf("Too many commands\n"));
	if (vars->n_command == 1)
		if (handle_single_builtin_new(vars, commands, data))
			return (1);
	init_pipes(vars);
	start_children_new(vars, data, cmds);
	close_pipes(vars);
	wait_all_childrens(data, vars);
	restore_fds(vars);
	free_exec(vars);
	//free(vars);
	return (0);
}
