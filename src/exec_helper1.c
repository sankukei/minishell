/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:53 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/21 23:10:19 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

int	check_if_builtin(char *str)
{
	if (!str)
		return (0);
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

void	check_for_heredoc(t_exec *vars, t_cmd *cmds)
{
	int		fd;
	t_cmd	*temp;
	t_redir	*temp_redirs;

	fd = 0;
	temp = cmds;
	while (temp)
	{
		temp_redirs = temp->redirs;
		while (temp_redirs)
		{
			if (temp_redirs->type == 1)
			{
				fd = write_heredoc_into_fd(temp_redirs->target);
				vars->heredoc = 1;
				vars->heredoc_fd = fd;
				if (fd >= 0)
					close(vars->heredoc_fd);
			}
			temp_redirs = temp_redirs->next;
		}
		temp = temp->next;
	}
}
