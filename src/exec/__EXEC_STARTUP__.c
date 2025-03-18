/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/17 20:11:56 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int __EXEC_STARTUP__(t_token *token)
{
	int	number_of_forks;
	int	p[2];
	pid_t	pid;
	int	status;

	//number_of_commands = get_command_number(); //theoretical
	i = number_of_commands;
	while (number_of_forks--)
	{
		//dup stdin dans le pipe 0
		//dup stdout dans le pipe 0
		if (i == number_of_commands)
			dup2(stdin, p[2]);	
		pid = fork();
		if (pid < 0)
		{
			write(1, "no", 2);
			exit(1);
		}
		else if (pid == 0)
		{
			//exec cmd;
			//execve(data->token_;
		}
	}
	while (wait(&status) > 0)
		;
	return (0);
}
