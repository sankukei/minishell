/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/13 01:21:24 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	__exec_startup__(t_data *data)
{
	t_exec 	*vars;

	vars = malloc(sizeof(t_exec));
	init_exec_variables(vars);
	vars->n_command = get_number_of_commands(data->token);
	if (vars->n_command > 100)
		return (printf("too many commands\n"));
	if (handle_single_builtin(vars, data))
		return (1);
	init_pipes(vars);
	start_children(vars, data);
	close_pipes(vars);
	wait_all_childrens(vars);
	restore_fds(vars);
	//free t_exec;
	return (0);
}
/*
int	OLD_EXEC(t_data *data)
{
	pid_t	pid;

	char	**args;
	char	*cmd;
	int	n;
	int	status;
	int 	old_stdin = dup(STDIN_FILENO);
	int 	old_stdout = dup(STDOUT_FILENO);
	int	**pipes;
	int	i = 0;
	int	temp;
	int	builtin;
	int	reddir = 0;
	int 	fd;

	fd = 1;
	i = 0;
	n = get_number_of_commands(data->token);
	if (n > 100)
		exit(1);
	cmd = data->token->str;
	builtin = check_if_builtin(cmd);
	reddir = check_if_redir(data->token);
	if (n == 1 && builtin != 0)
	{

		args = get_args(&data->token);
		if (reddir)
		{
			fd = get_fd_from_reddir(data->token->next->str, data->token->type);
		}
		exec_builtin(builtin, args, data, fd);
		free(args);
		return 1;
		exit(1);
	}
	temp = n;
	pipes = malloc(n * sizeof(int *));
	temp -= 1;
	while (temp--)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pid = fork();
		cmd = data->token->str;
		reddir = check_if_redir(data->token);
		args = get_args(&data->token);
		builtin = check_if_builtin(cmd);
		if (pid == 0)
		{
			if (reddir)
			{
				fd = get_fd_from_reddir(data->token->next->str, data->token->type);
			}
			if (i != n - 1)
			{
				close(pipes[i][0]);
				dup2(pipes[i][1], 1);
				close(pipes[i][1]);
			}
			if (i != 0)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], 0);
				close(pipes[i -1][0]);
			}
			close_all_pipes(pipes, i);
			if (builtin != 0)
			{
				exec_builtin(builtin, args, data, fd);
				exit(0);
			}
			if (!exec_single(data, cmd, args))
			{
				printf("execve failed\n");
				exit(0);
			}
			free(args);
		}
		i++;
	}
	i = 0;
	while (i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	while (wait(&status) > 0)
		 	;
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	 return (0);
}
*/


