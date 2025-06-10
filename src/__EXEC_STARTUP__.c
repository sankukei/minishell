/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/11 00:21:45 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exec_single(t_data *data, char *cmd, char **args)
{
	char	**path;
	char	*tmp;
	char	*test1;
	char	**str;
	int		i;

	path = ft_split(get_my_env2(data, "PATH"), ':');
	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		test1 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(test1, X_OK))
		{
			if (ft_strncmp(cmd, "ls", 3) == 0)
			{
				str = chang_args_ls(data, args);
				execve(test1, str, data->env);
			}
			execve(test1, args, data->env);
			free(test1);
			break;
		}
		free(test1);
		i++;
	}
	clear_double_array(path);
	write(1, "Command not found\n", 18);
	return (0);
}

int	get_number_of_commands(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 5)
			i++;
		token = token->next;
	}
	i++;
	return (i);
}

int	check_if_redir(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 1 || token->type == 2 || token->type == 3 || token->type == 4)
			return (1);
		token = token->next;
	}
	return (0);
}

int	get_cmd_len(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == 6 || token->type == 7)
	{
		i++;
		token = token->next;
	}
	return (i);
}

char	**get_args(t_token **token)
{
	int		i;
	int		is_reddir;
	char	**res;
	t_token	*tmp;

	i = 0;
	tmp = *token;
	is_reddir = 0;
	while (token && (*token) && ((*token)->type == 6 || (*token)->type == 7))
	{
		i++;
		(*token) = (*token)->next;
	}
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	*token = tmp;
	while (token && (*token) && ((*token)->type != 5))
	{
		if ((*token)->type == 1 || (*token)->type == 2 || (*token)->type == 3 || (*token)->type == 4)
		{
			is_reddir = 1;	
			break;
		}
		res[i] = ft_strdup((*token)->str);
		if (!res[i])
		{
				//call free_arr();
		}
		(*token) = (*token)->next;
		i++;
	}
	// un peu de la magie noir, mais ca alligne le pointeur au prochain cmd pour pouvoir call get_args en boucle et en restant sur le debut du prochain pipe a chaque call
	// tldr -> sombre
	if (*token && (*token)->next && is_reddir == 0)
		(*token) = (*token)->next;
	res[i] = NULL;
	return (res);
}

void	close_all_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	check_if_builtin(char *str)
{
	int	len;

	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (7);
	return (0);
}

int	get_fd_from_reddir(char *fd_name, int type)
{
	int	fd;
	if (type == 4)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	else if (type == 3)
	{
		fd = open(fd_name, O_RDONLY);
		if (fd < 0)
			exit(1);
		dup2(fd, 0);
	}
	else if (type == 2)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	return (fd);
}

void	exec_builtin(int selector, char **args, t_data *data, int fd)
{
	if (selector == 1)
		echo(args, fd);
	else if (selector == 2)
		cd(args);
	else if (selector == 3)
		pwd(args, fd);
	else if (selector == 4)
		export(data, args);
	else if (selector == 5)
		unset(data, args);
	else if (selector == 6)
		env(data);
	else if (selector == 7)
		ft_exit(data, args);
	return ;
}

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

/////////
void	init_exec_variables(t_exec *vars, t_data *data)
{
	vars->old_stdin = dup(STDIN_FILENO);
	vars->old_stdout = dup(STDOUT_FILENO);
	vars->fd = 1;
	vars->is_reddir = 0;
	vars->n_command = 0;
	vars->is_builtin = 0;
	vars->cmd = 0;
}

void	init_pipes(t_exec *vars)
{
	int	i;
	int	n;

	i = 0;
	n = vars->n_command;
	vars->pipes = malloc(n * sizeof(int *));
	n--;
	while (n--)
	{
		vars->pipes[i] = malloc(sizeof(int) * 2);
		pipe(vars->pipes[i]);
		i++;
	}
}

int	handle_single_builtin(t_exec *vars, t_data *data)
{
	vars->is_builtin = check_if_builtin(data->token->str);
	vars->is_reddir = check_if_redir(data->token);
	if (vars->n_command == 1 && vars->is_builtin != 0)
	{
		vars->args = get_args(&data->token);
		if (vars->is_reddir)
			vars->fd = get_fd_from_reddir(data->token->next->str,
					data->token->type);
		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
		return (1);
		//free args and *args++;
	}
	return (0);
}

void	children_exec(t_exec *vars, t_data *data, int i)
{
	if (vars->is_reddir)
		vars->fd = get_fd_from_reddir(data->token->next->str,
				data->token->type);
	if (i != vars->n_command - 1)
	{
		close(vars->pipes[i][0]);
		dup2(vars->pipes[i][1], STDOUT_FILENO);
		close(vars->pipes[i][1]);
	}
	if (i != 0)
	{
		close(vars->pipes[i - 1][1]);
		dup2(vars->pipes[i - 1][0], STDIN_FILENO);
		close(vars->pipes[i - 1][0]);
	}
	while (vars->xd < vars->n_command - 1)
	{
		close(vars->pipes[vars->xd][0]);
		close(vars->pipes[vars->xd][1]);
		vars->xd++;
		// A FIX PLUS TARD
		// pour une raison sombre je n'arrive pas a closes les pipes dans une fonction helper, a investiguer
	}
	if (vars->is_builtin != 0)
		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
	else if (!exec_single(data, vars->cmd, vars->args))
		printf("execve failed\n");
	exit(0);
}

void	start_children(t_exec *vars, t_data *data)
{
	int	i;

	i = 0;
	while (i < vars->n_command)
	{
		vars->pid = fork();
		vars->cmd = data->token->str;
		vars->is_reddir = check_if_redir(data->token);
		vars->args = get_args(&data->token);
		vars->is_builtin = check_if_builtin(vars->cmd);
		vars->xd = 0;
		if (vars->pid == 0)
			children_exec(vars, data, i);
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
	close(vars->old_stdin);
	dup2(vars->old_stdout, STDOUT_FILENO);
	close(vars->old_stdout);
}

// NEW EXEC
int	__exec_startup__(t_data *data)
{
	int	i;
	t_exec 	*vars;

	i = 0;
	vars = malloc(sizeof(t_exec));
	init_exec_variables(vars, data);
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
	return (0);
}
