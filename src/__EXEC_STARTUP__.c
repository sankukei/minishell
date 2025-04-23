/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/04/23 20:21:22 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exec_single(char *cmd)
{
	char	**path;
	int	does_exist;

	does_exist = 0;
	path = ft_split(getenv("PATH"), ':');
	while (*path)
	{
		if (access(*path, X_OK))
			does_exist = 1;
		*path++;
	}
	if (does_exist == 1)
		//execve
	else
		write(1, "Command not found\n", 18);
	return (0);
}

int	__EXEC_STARTUP__(t_token *token)
{
	while (token)
	{
		printf("EXEC %s\n", token->str);
		token = token->next;
	}
/*	int	number_of_forks;
	int	p[2];
	pid_t	pid;
	int	status;

	//number_of_commands = get_command_number(); //theoretical
	i = number_of_commands;
	while (number_of_forks--)
	{
		//dup stdin dans le pipe 0
		//dup stdout dans le pipe 0
		if (dup2(oldfd, newfd) == -1)
		{
			write(1, "error", 5);
			exit(1);
		}
		if (i == number_of_commands)
			dup2(stdin, p[2]);
		else
			dup2(p[2], stdout);
		pid = fork();
		if (pid < 0)
		{
			write(1, "no", 2);
			exit(1);
		}
		else if (pid == 0)
		{
			execve(token->str)
			//execve(data->token_;
		}
	}
	while (wait(&status) > 0)
		;
	return (0);
*/
}
