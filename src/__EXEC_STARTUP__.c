/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __EXEC_STARTUP__.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:11:55 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/05 03:08:34 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


static char *get_my_env2(t_data *data, char *str)
{
	char **env;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	env = data->env;
	if (ft_strncmp(str, "?", 2) == 0)
		return (ft_itoa_stack(data->last_exit_status));
	while (env[i])
	{
		//printf("je check la\n");
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			j++;
			return (&env[i][j]);
		}			
		i++;
	}
	return (NULL);
}


void	cd(char **args)
{
	char	*path;
	int	i;

	i = 0;
	args++;
	while (args[i])
		i++;
	if (i == 0)
	{
		chdir("/home");
		path = getcwd(NULL, 0);
	}
	else if (i == 1)
	{
		chdir(*args);
		path = getcwd(NULL, 0);
		printf("PWD -> %s\n", path);
	}
	else
		write(1, "too many arguments\n", 19);
}

void	pwd(char **args, int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}

void	echo(char **args, int fd)
{
	int	backslash;
	int 	i = 0;
	char	*str;

	backslash = 0;
	if (args[1])
	{
		args++;
		if (ft_strncmp(*args, "-n", ft_strlen(*args)) == 0)
		{
			backslash = 1;
			args++;
		}
	}
	else
	{
		write(fd, "\n", 1);
		return ;
	}
	i = 0;
	while (args[i])
		i++;
	str = ft_join(i, args, " ");
	write(1, str, ft_strlen(str));
	if (!backslash)
		write(fd, "\n", 1);
}
//###############################################################################
//								export & unset functions utils 
static int	var_name_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

static int	is_same_var(char *env_entry, char *arg)
{
	int	len;

	len = var_name_len(arg);
	if (!env_entry)
		return (0);
	if (ft_strlen(env_entry) < len)
		return (0);
	if (ft_strncmp(env_entry, arg, len) != 0)
		return (0);
	if (env_entry[len] != '=')
		return (0);
	return (1);
}

static int	count_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

void	env(t_data *data);
//###############################################################################
//							export

static int	handle_export_error(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		env(data);
		return (1);
	}
	if (args[1][0] == '=')
	{
		printf("\"%s\": not a valid identifier\n", args[1]);
		return (1);
	}
	while (args[1][i] && args[1][i] != '=')
	{
		if ((!ft_isalpha(args[1][i]) && !ft_isdigit(args[1][i])))
		{
			printf("\"%s\": not a valid identifier\n", args[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	export(t_data *data, char **args)
{
	char	**new_env;
	int		i;
	int		j;
	int		exist;

	if (handle_export_error(data, args))
		return ;
	exist = 0;
	i = count_env_size(data->env);
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	j = 0;
	while (j < i)
	{
		if (is_same_var(data->env[j], args[1])) // pour remplacer une variable existant dans l env
		{
			free(data->env[j]);
			new_env[j] = ft_strdup(args[1]);
			exist = 1;
		}
		else
			new_env[j] = data->env[j];		// sinon on copie
		j++;
	}
	if (!exist)
		new_env[j++] = ft_strdup(args[1]); // si elle existe pas on l ajoute a la fin
	new_env[j] = NULL;
	if (!exist)
		free(data->env);
	data->env = new_env;
	return ;
}
//###############################################################################
//							unset
void	unset(t_data *data, char **args)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;
	int		skip;

	i = 0;
	k = count_env_size(data->env);
	new_env = malloc(sizeof(char *) * (k + 1));
	if (!new_env)
		return ;
	j = 0;
	while (data->env[i])
	{
		skip = 0;
		k = 1;
		while (args[k])
		{
			if (is_same_var(data->env[i], args[k++]))	// on regarde si elle est dans l env
			{
				skip = 1;
				break ;
			}
		}
		if (!skip)
			new_env[j++] = data->env[i];	// si non on copie et j++
		else
			free(data->env[i]);			// ou on free
		i++;
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
}

//###############################################################################
void	env(t_data *data)
{
	int		i;
	char	**env;

	i = 0;
	env = data->env;
	while (env[i])
		printf("%s\n", env[i++]);
}

void	ft_exit(t_data *data, char **args)
{
	if (args[1])
	{
		printf("%s\n", "exit");
		exit_program(data);
		exit(ft_atoi(args[1])); // check le atoi si la range est assez grande du atoi		
	}
	else
	{
		printf("%s\n", "exit");
		exit_program(data);
		exit(data->last_exit_status);	
	}
	// si il n'y a pas d 'args[1] tu exit avec le dernier $? qui tu as TODO
	// Apres avoir gerer les signaux faire en sort que si on est dans un pipe ca printf pas exit
}

static char	**chang_args_ls(t_data *data, char **args)
{
	int		count;
	char	**new_args;
	int		i;

	(void)data;
	count = 0;
	while (args[count])
		count++;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);

	new_args[0] = ft_strdup("ls");
	new_args[1] = ft_strdup("--color=auto"); // parce que args= {ls,--color=auto, -l etc..}

	i = 1;
	while (i < count)
	{
		new_args[i + 1] = ft_strdup(args[i]);  // ajoute les flags de ls apres 
		i++;
	}
	new_args[i + 1] = NULL;
	return (new_args); //sjp si faudrai free a voir
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

int	check_if_redir(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 1 || token->type == 2 || token->type == 3 || token->type == 4)
			return (1);
		token = token->next;
	}
	return (0);
}

int	get_cmd_len(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == 6 || token->type == 7)
	{
		i++;
		token = token->next;
	}
	return (i);
}

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

int	get_fd_from_reddir(char *fd_name, int type)
{
	int	fd;
	if (type == 4)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	else if (type == 3)
	{
		fd = open(fd_name, O_RDONLY);
		if (fd < 0)
			exit(1);
		dup2(fd, 0);
	}
	else if (type == 2)
	{
		fd = open(fd_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
	}
	return (fd);
}

void	exec_builtin(int selector, char **args, t_data *data, int fd)
{
	if (selector == 1)
		echo(args, fd);
	else if (selector == 2)
		cd(args);
	else if (selector == 3)
		pwd(args, fd);
	else if (selector == 4)
		export(data, args);
	else if (selector == 5)
		unset(data, args);
	else if (selector == 6)
		env(data);
	else if (selector == 7)
		ft_exit(data, args);
	return ;
}

int	__exec_startup__(t_data *data)
{
	pid_t	pid;

	char	**args;
	char	*cmd;
	int	n;
	int	status;
	int 	old_stdin = dup(STDIN_FILENO);
	int 	old_stdout = dup(STDOUT_FILENO);
	int	**pipes;
	int	i = 0;
	int	temp;
	int	builtin;
	int	reddir = 0;
	int 	fd;

	fd = 1;
	i = 0;
	n = get_number_of_commands(data->token);
	if (n > 100)
		exit(1);
	cmd = data->token->str;
	builtin = check_if_builtin(cmd);
	reddir = check_if_redir(data->token);
	if (n == 1 && builtin != 0)
	{

		args = get_args(&data->token);
		if (reddir)
		{
			fd = get_fd_from_reddir(data->token->next->str, data->token->type);
		}
		exec_builtin(builtin, args, data, fd);
		free(args);
		return 1;
		exit(1);
	}
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
		cmd = data->token->str;
		reddir = check_if_redir(data->token);
		args = get_args(&data->token);
		int	a = 0;
		builtin = check_if_builtin(cmd);
		if (pid == 0)
		{
			if (reddir)
			{
				fd = get_fd_from_reddir(data->token->next->str, data->token->type);
			}
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
			if (builtin != 0)
			{
				exec_builtin(builtin, args, data, fd);
				exit(0);
			}
			if (!exec_single(data, cmd, args))
			{
				printf("execve failed\n");
				exit(0);
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

/////////
void	init_exec_variables(t_exec *vars, t_data* data)
{
	vars->old_stdin = dup(STDIN_FILENO);
	vars->old_stdout = dup(STDOUT_FILENO);
	vars->fd = 1;
	vars->is_reddir = 0;
	vars->n_command = 0;
	vars->is_builtin = 0;
	vars->cmd = 0;
}

void	handle_single_builtin(t_exec *vars, t_data *data)
{
	if (vars->n > 100)
		return (printf("too many commands\n"));
	vars->is_builtin = check_if_builtin(data->token->str);
	vars->is_reddir = check_if_reddir(data->token);
	if (vars->n == 1 && vars->is_builtin != 0)	
	{
		vars->args = get+args(&data->token);
		if (is_reddir)
			vars->fd = get_fd_from_reddir(data->token->next->str, data->token->type);
		exec_builtin(vars->is_builtin, vars->args, data, vars->fd);
		//free args and *args++;
		return (1);
	}
}

int	new_exec(t_data *data)
{
	int	i;
	int	check;
	t_exec *vars;

	i = 0;
	check = 0;

	init_exec_variables(vars, data);
	check = hande_single_builtin(vars, data);
	// si init pipes s'execute, cela veut dire que
	if (!check)
		init_pipes();

	return (0);
}
