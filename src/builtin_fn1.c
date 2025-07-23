/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:14:13 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/23 15:13:55 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_my_env2(t_data *data, char *str)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = data->env;
	if (ft_strncmp(str, "?", 2) == 0)
		return (ft_itoa_stack(data->last_exit_status));
	while (env[i])
	{
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

void	cd_helper(t_data *data, char *path, int i, char **args)
{
	char	*home;

	(void)path;
	if (i == 0)
	{
		home = get_my_env2(data, "HOME");
		if (!home)
			return (data->last_exit_status = 1, (void)0);
		chdir(home);
	}
	else if (i == 1)
	{
		if (chdir(*args) < 0)
		{
			printf("cd: no such file or directory: %s\n", *args);
			return (data->last_exit_status = 1, (void)0);
		}
	}
	else
	{
		write(1, "too many arguments\n", 19);
		data->last_exit_status = 2;
	}
}

void	cd(t_data *data, char **args)
{
	char	*path;
	int		i;

	data->last_exit_status = 0;
	i = 0;
	path = getcwd(NULL, 0);
	if (!path)
		return ((void)(data->last_exit_status = 1));
	args++;
	while (args[i])
		i++;
	cd_helper(data, path, i, args);
	free(path);
}

void	pwd(t_data *data, int fd)
{
	char	*path;

	data->last_exit_status = 0;
	path = getcwd(NULL, 0);
	if (!path)
	{
		data->last_exit_status = 1;
		return ;
	}
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	free(path);
}

void	echo(t_data *data, char **args, int fd)
{
	int		backslash;
	char	*str;

	backslash = 0;
	if (!args[1])
		return ((void)(write(fd, "\n", 1)));
	args++;
	if (check_flag(*args))
	{
		backslash = 1;
		args++;
	}
	str = join_args(args);
	if (!str)
	{
		data->last_exit_status = 1;
		return ;
	}
	if (str)
		write(fd, str, ft_strlen(str));
	if (!backslash)
		write(fd, "\n", 1);
	free(str);
	data->last_exit_status = 0;
}
