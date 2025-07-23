/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fn3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:14:27 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/23 15:11:09 by amedenec         ###   ########.fr       */
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

int	higher_number(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	check_for_no_equal(char *var_entry, char *arg)
{
	int	len;

	len = higher_number(ft_strlen(var_entry), ft_strlen(arg));
	if (ft_strncmp(var_entry, arg, len) == 0)
		return (1);
	return (0);
}

int	is_same_var(char *env_entry, char *arg)
{
	int	len;

	if (check_for_no_equal(env_entry, arg))
		return (1);
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
