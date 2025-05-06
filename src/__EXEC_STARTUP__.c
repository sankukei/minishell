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

int	exec_single(char *cmd, char **args)
{
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	while (*path)
	{
		char *tmp = ft_strjoin(*path, "/");
		char *test1 = ft_strjoin(tmp, cmd);
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
	int	i;
	char	**res;
	t_token *tmp;

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

int	__EXEC_STARTUP__(t_token *token)
{
	char	**args;
	char		*cmd;


	int	n;
	pid_t	pid;
	int	p[2];
	int	status;
	int	fd;
	char	*line;

	n = get_number_of_commands(token);
	// CHECK IF HEREDOC IN TOKENS -> if so while readline until EOF and feed it to execve as is
	int old_stdin = dup(STDIN_FILENO);
	int old_stdout = dup(STDOUT_FILENO);
	//old_stdin = dup(0);
	//old_stdout = dup(1);
//	if (n == 1)
//	{
//		cmd = token->str;
//		if (!(args = get_args(&token)))
//			return (0);	
//		exec_single(cmd, args);
//
//	}
	//array de pipe xd p[eut etyre 
	int	**pipes;

	pipes = malloc(n * sizeof(int *));
	int	i = 0;
	int	temp = n;
	temp -= 1;
	while (temp--)
	{
		
		printf("CREATE PIPE\n");
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pid = fork();
		cmd = token->str;
		args = get_args(&token);
		if (pid == 0)
		{
			fprintf(stderr, "iam %s n = %d\n", args[0], i);
			fflush(stderr);
			if (i != n - 1)
			{
				close(pipes[i][0]);
				dup2(pipes[i][1], 1);
				close(pipes[i][1]);
				fprintf(stderr, "iam et j'ecris dans le pipe %s n = %d\n", args[0], i);
			}
			if (i != 0)
			{
				fprintf(stderr, "iam et je lis dans le pipe %s n = %d\n", args[0], i);
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], 0);
				close(pipes[i -1][0]);
			}
			//FONCTION QUI CLOSE TOUTE LRRAY DE PIPE
			if (!exec_single(cmd, args))
			{
				write(1, "pranked\n", 7);
				return(0);
			}
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
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	dup2(old_stdout, STDOUT_FILENO);
	close(old_stdout);
	fprintf(stderr, "youhou je sors\n");
	// int	number_of_forks;
	// int	p[2];
	// pid_t	pid;
	// int	status;

	// //number_of_commands = get_command_number(); //theoretical
	// i = number_of_commands;
	// while (number_of_forks--)
	// {
	// 	//dup stdin dans le pipe 0
	// 	//dup stdout dans le pipe 0
	// 	if (dup2(oldfd, newfd) == -1)
	// 	{
	// 		write(1, "error", 5);
	// 		exit(1);
	// 	}
	// 	if (i == number_of_commands)
	// 		dup2(stdin, p[2]);
	// 	else
	// 		dup2(p[2], stdout);
	// 	pid = fork();
	// 	if (pid < 0)
	// 	{
	// 		write(1, "no", 2);
	// 		exit(1);
	// 	}
	// 	else if (pid == 0)
	// 	{
	// 		execve(token->str)
	// 		//execve(data->token_;
	// 	}
	// }
	// while (wait(&status) > 0)
	// 	;
	// return (0);

}
