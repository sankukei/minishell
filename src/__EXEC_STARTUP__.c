/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/02 23:32:06 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	cd(char **args)
{
	char	*path;
	int	i;

	i = 0;
	args++;
	while (args[i])
		i++;
	if (i == 0)
	{
		chdir("/home");
		path = getcwd(NULL, 0);
	}
	else if (i == 1)
	{
		chdir(*args);
		path = getcwd(NULL, 0);
		printf("PWD -> %s\n", path);
	}
	else
		write(1, "too many arguments\n", 19);
}

void	pwd(char **args)
{
	char	*path;
	int	fd;

	fd = 1;
	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}

void	echo(char **args)
{
	int	backslash;
	int	fd = 1;
	int 	i = 0;
	char	*str;

	backslash = 0;
	if (args[1])
	{
		args++;
		if (ft_strncmp(*args, "-n", ft_strlen(*args)) == 0)
		{
			backslash = 1;
			args++;
		}
	}
	else
	{
		write(fd, "\n", 1);
		return ;
	}
	i = 0;
	while (args[i])
		i++;
	str = ft_join(i, args, " ");
	write(1, str, ft_strlen(str));
	if (!backslash)
		write(fd, "\n", 1);
}

void	export(char **args)
{
	;
}

void	unset(char **args)
{
	;
}

void	env(char **args)
{
	;
}

int	exec_single(t_data *data, char *cmd, char **args)
{
	char	**path;
	char	*tmp;
	char	*test1;

	path = ft_split(get_my_env(data, "PATH"), ':');
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		test1 = ft_strjoin(tmp, cmd);
		if (!access(test1, X_OK))
		{
			execve(test1, args, NULL);
			return (1);
		}
		*path++;
	}
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

void	exec_builtin(int selector, char **args)
{
	if (selector == 1)
		echo(args);
	else if (selector == 2)
		cd(args);
	else if (selector == 3)
		pwd(args);
	else if (selector == 4)
		export(args);
	else if (selector == 5)
		unset(args);
	else if (selector == 6)
		env(args);
	else if (selector == 7)
		return ;
	//	exit(args);
}

int	__exec_startup__(t_data *data)
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

	i = 0;
	n = get_number_of_commands(data->token);
	if (n > 100)
		exit(1);
	cmd = data->token->str;
	builtin = check_if_builtin(cmd);
	if (n == 1 && builtin != 0)
	{
		args = get_args(&data->token);
		exec_builtin(builtin, args);
		free(args);
		return 1;
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
		int	a = 0;
		builtin = check_if_builtin(cmd);
		if (pid == 0)
		{
			if (reddir)
			{
				int fd;
				if (data->token->type == 4)
				{
					fd = open(data->token->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
					if (fd < 0)
						exit(1);
					dup2(fd, 1);
					// close(fd);
				}
				else if (data->token->type == 3)
				{
					fd = open(data->token->next->str, O_RDONLY);
					if (fd < 0)
						exit(1);
					dup2(fd, 0);
					// close(fd);
				}
				else if (data->token->type == 2)
				{
					fd = open(data->token->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
					if (fd < 0)
						exit(1);
					dup2(fd, 1);
					// close(fd);
				}
				close(fd);

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
				exec_builtin(builtin, args);
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
