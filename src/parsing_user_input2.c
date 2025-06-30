/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:01:14 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 07:52:41 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_my_env(t_data *data, char *str)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = data->env;
	if (ft_strncmp(str, "?", 2) == 0)
		return (free(str), ft_itoa_stack(data->last_exit_status));
	while (env[i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			j++;
			return (free(str), &env[i][j]);
		}
		i++;
	}
	return (free(str), NULL);
}

// LES DEUX FONTIONS EN DESSOUS SONT DES V1
// void	var_env_handler(t_data *data)
// {
// 	char	*input;
// 	char	*var;
// 	int		i;
// 	int		len;

// 	input = data->input;
// 	i = 0;
// 	while (input[i])
// 	{
// 		quote_check(data, i);
// 		if (input[i] == '$' && data->single_quote != true)
// 		{
// 			var = detect_var_env(&input[i]);
// 			len = count_var_len(&input[i]);
// 			if (len == 0)
// 				free(var);
// 			if (len && var_is_in_env(data, var, len))
// 			{
// 				var = get_my_env(data, var);
// 				replace_var_env(data, var, i, len);
// 				free(input);
// 				input = data->input;
// 			}
// 		}
// 		i++;
// 	}
// }

// static void	handle_env_variable(t_data *data, char **input, int i)
// {
// 	char	*var;
// 	int		len;

// 	var = detect_var_env(&(*input)[i]);
// 	len = count_var_len(&(*input)[i]);
// 	if (len == 0)
// 		return (free(var));
// 	if (var_is_in_env(data, var, len))
// 	{
// 		var = get_my_env(data, var);
// 		replace_var_env(data, var, i, len);
// 		free(*input);
// 		*input = data->input;
// 	}
// }

// void	var_env_handler(t_data *data)
// {
// 	char	*input;
// 	int		i;

// 	input = data->input;
// 	i = 0;
// 	while (input[i])
// 	{
// 		printf("%c", input[i]);
// 		quote_check(data, i);
// 		if (input[i] == '$' && data->single_quote != true)
// 			handle_env_variable(data, &input, i);
// 		i++;
// 	}
// }


static int	handle_env_variable(t_data *data, char **input, int i)
{
	char	*var;
	int		len;
	char	*value;
	int		value_len;

	var = detect_var_env(&(*input)[i]);
	len = count_var_len(&(*input)[i]);
	if (len == 0)
	{
		free(var);
		return (1);
	}

	if (var_is_in_env(data, var, len))
	{
		value = get_my_env(data, var);
		value_len = ft_strlen(value);

		replace_var_env(data, value, i, len);

		free(*input);
		*input = data->input;

		return (value_len);
	}
	return (len + 1);
}


void	var_env_handler(t_data *data)
{
	char	*input;
	int		i;
	int		step;

	i = 0;
	input = data->input;
	while (input[i])
	{
		quote_check(data, i);
		if (input[i] == '$' && data->single_quote != true)
		{
			step = handle_env_variable(data, &input, i);
			i += step;
			continue ;
		}
		i++;
	}
	data->input = input;
}


int	check_quote_error(t_data *data)
{
	char		*input;

	input = data->input;
	while (*input)
	{
		if ((*input == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
		else if ((*input == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
		input++;
	}
	if (data->single_quote || data->double_quote)
	{
		data->single_quote = false;
		data->double_quote = false;
		printf("une quote n'est pas ferme\n");
		return (1);
	}
	return (0);
}

void	copy_var_name(char *dest, char *src)
{
	while (*src && *src != ' ' && (ft_isalnum(*src) || *src == '_'))
		*dest++ = *src++;
	*dest = '\0';
}
