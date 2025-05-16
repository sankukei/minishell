/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sankukei <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/04/27 17:53:35 by sankukei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	cd(int arg_count, char *arg)
{
	char	*path;

	if (arg_count == 1)
	{
		chdir("/home/$NAME");
		return ;
	}
	else if (arg_count == 2)
	{
		if (chdir(arg) == 0)
			;
		else
			write(1, "error\n", 6);
	}
	else
		write(1, "too many arguments\n", 19);
	printf("PWD -> %s\n", path);
	chdir("test");
	path = getcwd(NULL, 0);
	printf("PWD -> %s\n", path);
	free(path);
}

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	echo(void)
{
	;
}

int	exec_single(char *cmd, char **args)
{
	char	**path;
	char	*tmp;
	char	*test1;

	path = ft_split(getenv("PATH"), ':');
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

char	**get_args(t_token **token)
{
	int		i;
	char	**res;
	t_token	*tmp;

	i = 0;
	tmp = *token;
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
	while (token && (*token) && ((*token)->type == 6 || (*token)->type == 7))
	{
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
	if (*token && (*token)->next)
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

		len = ft_strlen(str);
		if (ft_strncmp(str, "echo", len) == 0)
				return (1);
		else if (ft_strncmp(str, "cd", len) == 0)
				return (1);
		else if (ft_strncmp(str, "pwd", len) == 0)
				return (1);
		else if (ft_strncmp(str, "export", len) == 0)
				return (1);
		else if (ft_strncmp(str, "unset", len) == 0)
				return (1);
		else if (ft_strncmp(str, "env", len) == 0)
				return (1);
		else if (ft_strncmp(str, "exit", len) == 0)
				return (1);
		return (0);
}

int	__exec_startup__(t_token *token)
{
	char	**args;
	char		*cmd;
	int	n;

	pid_t	pid;
	int	status;
	int old_stdin = dup(STDIN_FILENO);
	int old_stdout = dup(STDOUT_FILENO);
	int	**pipes;
	int	i = 0;
	int	temp;

	// if bultin
	// 	exec_builtin
	// else
	//

	n = get_number_of_commands(token);
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
		cmd = token->str;
		if (check_if_builtin(cmd) != 0)
		{
				printf("ASDLKASLDJAS:DL");
		}
		args = get_args(&token);
		if (pid == 0)
		{
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
			if (!exec_single(cmd, args))
			{
				write(1, "pranked\n", 7);
				return(0);
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
