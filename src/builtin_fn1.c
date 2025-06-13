/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:14:13 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/13 02:17:16 by leothoma         ###   ########.fr       */
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

void	pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(fd, path, ft_strlen(path));
	write(fd, "\n", 1);
}

void	echo(char **args, int fd)
{
	int		backslash;
	int		i;
	char	*str;

	i = 0;
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
