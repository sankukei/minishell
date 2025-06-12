#include "../headers/minishell.h"

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
			break;
		}
		free(test1);
		i++;
	}
	clear_double_array(path);
	write(1, "Command not found\n", 18);
	return (0);
}

int	handle_single_builtin(t_exec *vars, t_data *data)
{
	vars->is_builtin = check_if_builtin(data->token->str);
	vars->is_reddir = check_if_redir(data->token);
	if (vars->n_command == 1 && vars->is_builtin != 0)
	{
		vars->args = get_args(&data->token);
		if (vars->is_reddir)
			vars->fd = get_fd_from_reddir(data->token->next->str,
					data->token->type);
		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
		return (1);
		//free args and *args++;
	}
	return (0);
}
void	start_children(t_exec *vars, t_data *data)
{
	int	i;

	i = 0;
	while (i < vars->n_command)
	{
		vars->pid = fork();
		vars->cmd = data->token->str;
		vars->is_reddir = check_if_redir(data->token);
		vars->args = get_args(&data->token);
		vars->is_builtin = check_if_builtin(vars->cmd);
		vars->xd = 0;
		if (vars->pid == 0)
			children_exec(vars, data, i);
		i++;
		//free args and *args++;
	}
}

void	children_exec(t_exec *vars, t_data *data, int i)
{
	if (vars->is_reddir)
		vars->fd = get_fd_from_reddir(data->token->next->str,
				data->token->type);
	if (i != vars->n_command - 1)
	{
		close(vars->pipes[i][0]);
		dup2(vars->pipes[i][1], STDOUT_FILENO);
		close(vars->pipes[i][1]);
	}
	if (i != 0)
	{
		close(vars->pipes[i - 1][1]);
		dup2(vars->pipes[i - 1][0], STDIN_FILENO);
		close(vars->pipes[i - 1][0]);
	}
	while (vars->xd < vars->n_command - 1)
	{
		close(vars->pipes[vars->xd][0]);
		close(vars->pipes[vars->xd][1]);
		vars->xd++;
		// A FIX PLUS TARD
		// pour une raison sombre je n'arrive pas a closes les pipes dans une fonction helper, a investiguer
	}
	if (vars->is_builtin != 0)
		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
	else if (!exec_single(data, vars->cmd, vars->args))
		printf("execve failed\n");
	exit(0);
}