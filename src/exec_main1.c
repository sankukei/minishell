/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:30 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/21 22:10:41 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exec_relative_path(t_data *data, char *cmd, char **args)
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

void	exec_single_helper(t_data *data, char *cmd, char **args, char **path)
{
	char	*tmp;
	int		i;
	char	*buffer;
	char	**str;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		buffer = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(buffer, X_OK))
		{
			if (ft_strncmp(cmd, "ls", 3) == 0)
			{
				str = chang_args_ls(data, args);
				execve(buffer, str, data->env);
			}
			execve(buffer, args, data->env);
		}
		free(buffer);
		i++;
	}
}

int	exec_single(t_data *data, char *cmd, char **args)
{
	char	**path;

	if (!cmd)
	{
		exit_child_process(data);
		return (0);
	}
	if (ft_strncmp(cmd, "/", 1) == 0)
		if (!exec_given_path(data, cmd, args))
			return (0);
	if (ft_strncmp(cmd, ".", 1) == 0)
		if (!exec_relative_path(data, cmd, args))
			return (0);
	path = ft_split(get_my_env2(data, "PATH"), ':');
	if (!path)
		return (0);
	exec_single_helper(data, cmd, args, path);
	clear_double_array(path);
	exit_child_process(data);
	return (0);
}

int	write_heredoc_into_fd(char *target)
{
	int					fd;
	char				*input;
	struct sigaction	sa;
	struct sigaction	old;
	t_mode				*mode;

	mode = get_shell_mode();
	fd = open(".heredoc_buffer", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	setup_sigint(&sa, &old, mode);
	while (1)
	{
		input = readline("heredoc> ");
		if (*get_sigint_flag())
			return (handle_sigint_for_heredoc(fd, input, &old, mode));
		if (!input)
			return (handle_eof(fd, target, &old, mode));
		if (is_delimiter(input, target))
			break ;
		write_line(fd, input);
		free(input);
	}
	return (finish_heredoc(fd, input, &old, mode));
}
