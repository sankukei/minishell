/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/16 07:01:35 by adam             ###   ########.fr       */
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

// TODO faire la fonction qui permet de modifier l intput (origine)
// pour mettre les var d env a la place
void	var_env_handler(t_data *data)
{
	char	*input;
	char	*var;

	input = data->input;
	while (*input)
	{
		if ((*input == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
		else if ((*input == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
		if (*input == '$' && data->single_quote != true)
		{
			var = detect_var_env(input);
			//replace_var_env(data, var);
			if (getenv(var))
				printf("%s\n", getenv(var));
		}
		input++;
	}
}


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
	//TODO creat all tokens from the output user
	// check readme parsing
	//add_token(&data->token, "ls", 6);
}
