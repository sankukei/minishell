/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:30 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 01:06:57 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// char	**get_args(t_token **token, t_exec *vars)
// {
// 	int		is_reddir;
// 	int		count;
// 	int		filled;
// 	char	**res;
// 	t_token	*tmp;

// 	is_reddir = 0;
// 	tmp = *token;
// 	count = skip_first_tokens(token);
// 	res = alloc_args_array(count + 16);
// 	if (!res)
// 		return (NULL);
// 	*token = tmp;
// 	filled = fill_args(res, token, &is_reddir, vars);
// 	if (filled == -1)
// 	{
// 		free_arr(res);
// 		return (NULL);
// 	}

// 	while((*token) && (*token)->next && (*token)->type != 6)
// 	{
// 		if ((*token)-> type == APPEND || (*token)->type == TRUNC || (*token)->type == INPUT)
// 		{
// 			vars->reddir_fd_name = (*token)->next->str;
// 			vars->reddir_fd_type = (*token)->type;
// 		}
// 		*token = (*token)->next;
// 	}
// 	return (res);
// }

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
			break ;
		}
		free(test1);
		i++;
	}
	clear_double_array(path);
	write(1, "Command not found\n", 18);
	return (0);
}

// int	handle_single_builtin(t_exec *vars, t_data *data)
// {
// 	vars->is_builtin = check_if_builtin(data->token->str);
// 	vars->is_reddir = check_if_redir(data->token);
// 	if (vars->n_command == 1 && vars->is_builtin != 0)
// 	{
// 		vars->args = get_args(&data->token, vars);
// 		if (vars->is_reddir)
// 			vars->fd = get_fd_from_reddir(vars->reddir_fd_name,
// 					vars->reddir_fd_type, vars);
// 		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
// 		return (1);
// 	}
// 	return (0);
// }

void	align_pointer(t_token **token)
{
	while (token && *token && ((*token)->type == 6 || (*token)->type == 7))
		*token = (*token)->next;
}

int	write_heredoc_into_fd(char *target)
{
	char	*input;
	int	heredoc_fd;

	//TODO: changer les permission pour eviter les prankex en corrections
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

void	check_for_heredoc(t_cmd *cmds)
{
	int	fd;
	t_redir	*temp;

	fd = 0;
	if (!cmds->redirs)
		return ;
	temp = cmds->redirs;
	while (temp)
	{
		printf("adasdasdasdasdasdsadasdasd %s\n", temp->target);
		if (cmds->redirs->type == 1)
		{
			printf("HEREDOC FOUND\n");
			fd = write_heredoc_into_fd(temp->target);
		}
		temp = temp->next;
	}
}

// void	start_children(t_exec *vars, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vars->n_command)
// 	{
// 		vars->pid = fork();
// 		printf("N_COMMANDS -> %d, i = %d\n", vars->n_command, i);
// 		vars->is_reddir = check_if_redir(data->token);
// 		vars->cmd = data->token->str;
// 		vars->args = get_args(&data->token, vars);

// 		 printf("vars->cmd = %s, current_pipe_index = %d, heredoc_index = %d\n", vars->cmd, vars->current_pipe_index, vars->heredoc_index);
// 		 printf("vars->is_reddir = %d\n", vars->is_reddir);
// 		 printf("vars->is_heredoc= %d\n", vars->is_heredoc);

// 		vars->is_builtin = check_if_builtin(vars->cmd);
// 		vars->xd = 0;
// 		if (vars->pid == 0)
// 			children_exec(vars, data, i);
// 		i++;
// 		vars->current_pipe_index = i;
// 	}
// }

// void	children_exec(t_exec *vars, t_data *data, int i)
// {
// 	if (vars->is_reddir)
// 		vars->fd = get_fd_from_reddir(vars->reddir_fd_name, vars->reddir_fd_type, vars);
// 	else if(!(setup_output_pipes(vars, i)) || !(setup_input_pipes(vars, i)))
// 	{
// 		free_exec(vars);
// 		exit(1);
// 	}
// 	// close_pipes(vars);
// 	if (vars->is_builtin != 0)
// 		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
// 	else if (!exec_single(data, vars->cmd, vars->args))
// 	{
// 		printf("execve failed\n");
// 		free_exec(vars);
// 		exit(1);
// 	}
// 	exit(0);
// }
