/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:49:26 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/16 14:22:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	setup_pipes(t_exec *vars, int i, t_data *data)
{
	if (!(setup_output_pipes(vars, i)) || !(setup_input_pipes(vars, i)))
	{
		clear_cmds(&data->cmd);
		free_exec(vars);
		exit(1);
	}
}

void	setup_redirs(t_cmd *cmds, t_data *data, t_exec *vars, t_dup dups)
{
	if (cmds->redirs)
	{
		dups = handle_redir(data, cmds->redirs, vars);
		handle_dups(dups);
	}
}

void	children_exec_new(t_exec *vars, t_data *data, int i, t_cmd *cmds)
{
	t_dup	dups;

	ft_bzero(&dups, sizeof(dups));
	setup_pipes(vars, i, data);
	setup_redirs(cmds, data, vars, dups);
	close_unused_pipes(data, vars, i);
	if (check_if_builtin(cmds->cmd[0]))
	{
		exec_builtin(check_if_builtin(cmds->cmd[0]), cmds->cmd, data, dups);
		i = 0;
		while (i < vars->n_command - 1)
			free(vars->pipes[i++]);
		free(vars->pipes);
		free(vars);
	}
	else if (!(exec_single(data, cmds->cmd[0], cmds->cmd)))
	{
		free_exec(vars);
		clear_cmds(&data->cmd);
		free(data);
		exit(127);
	}
	clear_double_array(data->env);
	free(data);
	exit(0);
}

void	start_children_new(t_exec *vars, t_data *data, t_cmd *cmds)
{
	int		i;
	t_cmd	*commands;

	commands = cmds;
	i = 0;
	*get_shell_mode() = MODE_CHILD;
	update_sigquit();
	while (i < vars->n_command && commands && commands->cmd)
	{
		vars->pid = fork();
		if (vars->pid == 0)
			children_exec_new(vars, data, i, commands);
		i++;
		commands = commands->next;
	}
}

int	__exec_startup__(t_data *data, t_cmd *cmds)
{
	t_exec	*vars;
	t_cmd	*commands;

	vars = malloc(sizeof(t_exec));
	if (!vars)
		return (1);
	ft_bzero(vars, sizeof(t_exec));
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
	return (0);
}
