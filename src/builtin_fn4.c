/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:01:32 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/23 15:16:28 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_export_error(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		env(data, 1);
		data->last_exit_status = 0;
		return (1);
	}
	if (args[1][0] == '=')
	{
		printf("\"%s\": not a valid identifier\n", args[1]);
		return (data->last_exit_status = 2, 1);
	}
	while (args[1][i] && args[1][i] != '=')
	{
		if ((!ft_isalpha(args[1][i]) && !ft_isdigit(args[1][i])
			&& args[1][i] != '_'))
		{
			printf("\"%s\": not a valid identifier\n", args[1]);
			return (data->last_exit_status = 2, 1);
		}
		i++;
	}
	return (0);
}

static void	copy_env_with_export(t_data *data, char **args,
				char **new_env)
{
	int	i;
	int	j;
	int	found;

	j = 0;
	i = 0;
	found = 0;
	while (data->env[i])
	{
		if (is_same_var(data->env[i], args[1]))
		{
			new_env[j++] = ft_strdup(args[1]);
			found = 1;
		}
		else
		{
			new_env[j++] = ft_strdup(data->env[i]);
		}
		i++;
	}
	if (!found)
		new_env[j++] = ft_strdup(args[1]);
	new_env[j] = NULL;
}

void	export(t_data *data, char **args)
{
	char	**new_env;
	int		size;

	if (handle_export_error(data, args))
		return ;
	size = count_env_size(data->env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return ((void)(data->last_exit_status = 1));
	ft_bzero(new_env, sizeof(char *) * (size + 2));
	copy_env_with_export(data, args, new_env);
	clear_double_array(data->env);
	data->env = new_env;
	data->bool_for_free_env = 1;
	data->last_exit_status = 0;
}

void	ft_exit(t_data *data, char **args)
{
	printf("%s\n", "exit");
	exit_program(data, args);
}
