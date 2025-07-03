/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:30 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 03:51:03 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	exec_given_path(t_data *data, char *cmd, char **args)
{
	if (!access(cmd, X_OK))
	{
		if (ft_strnstr(cmd, "ls", ft_strlen(cmd)))
		{
			args = chang_args_ls(data, args);
			execve("ls", args, data->env);
		}
		execve(cmd, args, data->env);
		return (0);
	}
	return (1);
}

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
	if (ft_strncmp(cmd, "/", 1) == 0)
		if (!exec_given_path(data, cmd, args))
			return (0);
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
			break ;
		}
		free(test1);
		i++;
	}
	clear_double_array(path);
	write(1, "Command not found\n", 18);
	return (0);
}

void	align_pointer(t_token **token)
{
	while (token && *token && ((*token)->type == 6 || (*token)->type == 7))
		*token = (*token)->next;
}

int	write_heredoc_into_fd(char *target)
{
	char	*input;
	int		heredoc_fd;

	heredoc_fd = open(".heredoc_buffer", O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = 0;
	while (1)
	{
		input = readline("heredoc> ");
		if (ft_strncmp(input, target, ft_strlen(target) + 1) == 0)
			break ;
		if (ft_strlen(input))
		{
			write(heredoc_fd, input, ft_strlen(input));
			write(heredoc_fd, "\n", 1);
		}
		free(input);
	}
	free(input);
	close(heredoc_fd);
	return (heredoc_fd);
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
				close(vars->heredoc_fd);
			}
			temp_redirs = temp_redirs->next;
		}
		temp = temp->next;
	}
}
