/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:14:13 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 02:16:19 by amedenec         ###   ########.fr       */
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

void	cd(char **args)
{
	char	*path;
	int		i;

	i = 0;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	args++;
	while (args[i])
		i++;
	if (i == 0)
	{
		chdir("/home");
	}
	else if (i == 1)
	{
		chdir(*args);
		printf("PWD -> %s\n", path);
	}
	else
		write(1, "too many arguments\n", 19);
	free(path);
}

void	pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
	free(path);
}

void	echo(char **args, int fd)
{
	int		backslash;
	char	*str;

	backslash = 0;
	if (!args[1])
	{
		write(fd, "\n", 1);
		return ;
	}
	args++;
	if (check_flag(*args))
	{
		backslash = 1;
		args++;
	}
	str = join_args(args);
	if (str)
		write(fd, str, ft_strlen(str));
	if (!backslash)
		write(fd, "\n", 1);
}

void	ft_exit(t_data *data, char **args)
{
	if (args[1])
	{
		printf("%s\n", "exit");
		exit_program(data);
		exit(ft_atoi(args[1]));
	}
	else
	{
		printf("%s\n", "exit");
		exit_program(data);
		exit(data->last_exit_status);
	}
}
