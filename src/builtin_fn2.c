/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:13:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/13 02:19:31 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

// void	unset(t_data *data, char **args)
// {
// 	char	**new_env;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		skip;

// 	i = 0;
// 	k = count_env_size(data->env);
// 	new_env = malloc(sizeof(char *) * (k + 1));
// 	if (!new_env)
// 		return ;
// 	j = 0;
// 	while (data->env[i])
// 	{
// 		skip = 0;
// 		k = 1;
// 		while (args[k])
// 		{
// 			if (is_same_var(data->env[i], args[k++]))
// 			{
// 				skip = 1;
// 				break ;
// 			}
// 		}
// 		if (!skip)
// 			new_env[j++] = data->env[i];
// 		else
// 			free(data->env[i]);
// 		i++;
// 	}
// 	new_env[j] = NULL;
// 	free(data->env);
// 	data->env = new_env;
// }

static int	should_skip(char *env_var, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_same_var(env_var, args[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	copy_filtered_env(char **new_env, char **old_env, char **args, int *j)
{
	int	i;

	i = 0;
	while (old_env[i])
	{
		if (should_skip(old_env[i], args))
			free(old_env[i]);
		else
			new_env[(*j)++] = old_env[i];
		i++;
	}
}

void	unset(t_data *data, char **args)
{
	char	**new_env;
	int		size;
	int		j;

	/*
	 	faire une fonction pour verifier les erreurs
		notament pour "=" qui efface toutes lenv ??
	*/
	size = count_env_size(data->env);
	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return ;
	j = 0;
	copy_filtered_env(new_env, data->env, args, &j);
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
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
