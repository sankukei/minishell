/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/30 07:51:40 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <limits.h>

// me pas enlever pour l instant
// char	*detect_var_env(char *input)
// {
// 	int		len;
// 	char	*dest;
// 	char	*ptr;

// 	input++;
// 	ptr = input;
// 	len = 0;
// 	if (*input == '?')
// 	{
// 		dest = malloc(sizeof(char) * 2);
// 		dest[0] = '?';
// 		dest[1] = '\0';
// 		return (dest);
// 	}
// 	while (*input != ' ' && *input != '\0'
// 		&& (ft_isalnum(*input) == 1 || *input == '_'))
// 	{
// 		len++;
// 		input++;
// 	}
// 	dest = malloc(sizeof(char) * len + 1);
// 	while (*ptr != ' ' && *ptr != '\0'
// 		&& (ft_isalnum(*ptr) == 1 || *ptr == '_'))
// 		*dest++ = *ptr++;
// 	*dest = '\0';
// 	return (dest - len);
// }

static int	var_len(char *input)
{
	int	len;

	len = 0;
	while (*input && *input != ' '
		&& (ft_isalnum(*input) || *input == '_'))
	{
		len++;
		input++;
	}
	return (len);
}

char	*detect_var_env(char *input)
{
	int		len;
	char	*dest;
	char	*ptr;

	input++;
	ptr = input;
	if (*input == '?')
	{
		dest = malloc(2);
		if (!dest)
			return (NULL);
		dest[0] = '?';
		dest[1] = '\0';
		return (dest);
	}
	len = var_len(ptr);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	bzero(dest, len+1);
	copy_var_name(dest, ptr);
	return (dest);
}

int	count_var_len(char *input)
{
	int		len;

	input++;
	len = 0;
	if (*input == '?')
		return (1);
	while (*input != ' ' && *input != '\0'
		&& (ft_isalnum(*input) == 1 || *input == '_'))
	{
		len++;
		input++;
	}
	return (len);
}

void	replace_var_env(t_data *data, char *var, int i, int len)
{
	int		len_new_input;
	char	*dest;

	len_new_input = ft_strlen(data->input) + ft_strlen(var) - (len + 1);
	dest = malloc(sizeof(char) * len_new_input + 1);
	if (!dest)
	{
		exit(1);
	}
	bzero(dest, sizeof(char) * len_new_input + 1);
//	memset(dest, '\0', len_new_input);
	dest[len_new_input] = '\0';
	ft_strlcpy(dest, data->input, i + 1);
	ft_strlcpy(dest + i, var, ft_strlen(var) + 1);
	ft_strlcpy(dest + i + ft_strlen(var),
		data->input + i + len + 1, len_new_input);
	data->input = dest;
}

//"essaie de fix un truc de ouf mais c'etais pas ca"
// void	replace_var_env(t_data *data, char *value, int start, int var_len)
// {
// 	int		prefix_len;
// 	int		value_len;
// 	int		suffix_len;
// 	int		new_len;
// 	char	*new_input;
// 	if (!data || !data->input || !value)
// 		return ;
// 	prefix_len = start;
// 	value_len = ft_strlen(value);
// 	suffix_len = ft_strlen(data->input + start + var_len + 1);
// 	new_len = prefix_len + value_len + suffix_len;
// 	new_input = malloc(sizeof(char) * (new_len + 1));
// 	if (!new_input)
// 		exit(1);
// 	ft_memcpy(new_input, data->input, prefix_len);
// 	ft_memcpy(new_input + prefix_len, value, value_len);
// 	ft_memcpy(new_input + prefix_len + value_len,
// 		data->input + start + var_len + 1, suffix_len);
// 	new_input[new_len] = '\0';
// 	data->input = new_input;
// }


int	parsing(t_data	*data)
{
	if (check_quote_error(data))
		return (1);
	var_env_handler(data);
	tokenisation(data);
	data->front_token = data->token;
	type_tokens(data);
	if (check_token_syntax(data->token))
	 	return (1);
	extern_quote_handler(data);
	//affiche_token_test(data->token);
	return (0);
}
