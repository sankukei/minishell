/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/20 05:47:47 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*detect_var_env(char *input)
{
	int		len;
	char	*dest;
	char	*ptr;
	
	input++; // pour passer le $
	ptr = input;
	len = 0;
	while (*input != ' ' && *input  != '\0' && ft_iscapitalise(*input) == 1) // a voir si il faut mettre '\0'
	{
		len++;
		input++;
	}
	dest = malloc(sizeof(char) * len + 1);
	while (*ptr != ' ' && *ptr != '\0' && ft_iscapitalise(*ptr) == 1)
		*dest++ = *ptr++;
	*dest = '\0';
	return (dest - len);
}
int	count_var_len(char *input)
{
	int		len;
	
	input++; // pour passer le $
	len = 0;
	while (*input != ' ' && *input  != '\0' && ft_iscapitalise(*input) == 1) // a voir si il faut mettre '\0'
	{
		len++;
		input++;
	}
	return (len);
}
void	replace_var_env(t_data *data, char *var, int i, int len)
{
	//TODO
	int		len_new_input;
	char	*dest;
	char	*ptr;

	len_new_input = ft_strlen(data->input) + ft_strlen(var) - (len + 1);
	dest = malloc(sizeof(char) * len_new_input + 1);
	if (!dest)
	{
		// TODO free all clear exit;
		exit(1);
	}
	ptr = dest;
	memset(dest, '\0', len_new_input);
	dest[len_new_input] = '\0';
	ft_strlcpy(dest, data->input, i + 1);
	ft_strlcpy(dest + i, var, ft_strlen(var) + 1);
	ft_strlcpy(dest + i + ft_strlen(var), data->input + i + len + 1, len_new_input);
	data->input = dest;

}

void	var_env_handler(t_data *data)
{
	char	*input;
	char	*var;
	int		i;
	int		len;

	input = data->input;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
		else if ((input[i] == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
		if (input[i] == '$' && data->single_quote != true)
		{
			var = detect_var_env(&input[i]);
			len = count_var_len(&input[i]);
			if (getenv(var))
			{
				var = getenv(var);
				replace_var_env(data, var, i, len);
				input = data->input;
			}
		}
		i++;
	}
} // facile a norme, enelever input = data->input et remplacer tout les input par data->input

void	check_quote_error(t_data *data)
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
		printf("une quote n'est pas ferme\n");
		exit(0);
	}
}

void	parsing(t_data	*data)
{
	check_quote_error(data);
	var_env_handler(data);
	lexer(data, data->input);
	//TODO creat all tokens from the output user
	// check readme parsing
	//add_token(&data->token, "ls", 6);
}
