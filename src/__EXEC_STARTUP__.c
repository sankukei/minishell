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
	res = malloc(i * sizeof(char *) + 1);
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
	res[i] = 0;
	return (res);	
}

int	__EXEC_STARTUP__(t_token *token)
{
	char	**args;
	char		*cmd;

	cmd = token->str;
	if (!(args = get_args(&token)))
		return (0);	
	//exec_single(cmd, args);

	int	n;
	pid_t	pid;
	int	p[2];
	int	i;
	int	status;
	int	fd;
	char	*line;

	n = get_number_of_commands(token);
	i = n;
	// CHECK IF HEREDOC IN TOKENS -> if so while readline until EOF and feed it to execve as is
	while (n--)
	{
		pipe(p);
		if (i == n)
		{
			dup2(stdin, p[0]);
		}
		else
		{
			dup2(p[1], stdout);
		}
		pid = fork();
		if (pid == 0)
		{
			cmd = token->str;
			args = get_args(&token);
			if (!exec_single(cmd, args))
				return(0);
				//free et kill les child 
		}
		else
		{
			//send data to child ? 
		}
		while (wait(&status) > 0)
			 	;
	}

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
