/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/02 04:24:03 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	should_skip(char *env_var, char **args)
{
	int	k;

	k = 1;
	while (args[k])
	{
		if (is_same_var(env_var, args[k]))
			return (1);
		k++;
	}
	return (0);
}

void	unset(t_data *data, char **args)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = count_env_size(data->env);
	new_env = malloc(sizeof(char *) * (k + 1));
	if (!new_env)
		return ((void)(data->last_exit_status = 1));
	ft_bzero(new_env, sizeof(char *) * (k + 1));
	while (data->env[i])
	{
		if (should_skip(data->env[i], args))
			free(data->env[i]);
		else
			new_env[j++] = data->env[i];
		i++;
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
	data->last_exit_status = 0;
}

void	env(t_data *data)
{
	int		i;
	char	**env;

	i = 0;
	env = data->env;
	while (env[i])
		printf("%s\n", env[i++]);
}

char	**chang_args_ls(t_data *data, char **args)
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
	bzero(new_args, sizeof(char *) * (count + 2));
	new_args[0] = ft_strdup("ls");
	new_args[1] = ft_strdup("--color=auto");
	i = 1;
	while (i < count)
	{
		new_args[i + 1] = ft_strdup(args[i]);
		i++;
	}
	new_args[i + 1] = NULL;
	return (new_args);
}
