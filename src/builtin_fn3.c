/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:14:27 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 06:48:35 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	var_name_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	is_same_var(char *env_entry, char *arg)
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

int	count_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	handle_export_error(t_data *data, char **args)
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
	bzero(new_env, sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		if (is_same_var(data->env[j], args[1]))
		{
			free(data->env[j]);
			new_env[j] = ft_strdup(args[1]);
			exist = 1;
		}
		else
			new_env[j] = data->env[j];
		j++;
	}
	if (!exist)
		new_env[j++] = ft_strdup(args[1]);
	new_env[j] = NULL;
	if (!exist)
		free(data->env);
	data->env = new_env;
	return ;
}
