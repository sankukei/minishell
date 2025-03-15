/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:41:26 by amedenec          #+#    #+#             */
/*   Updated: 2025/03/15 04:06:51 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
void	replace_var_env(t_data *data)
{
	
}


void	check_quote_error(t_data *data)
{
	char	*input;
	t_boolen	single_quote;
	t_boolen	double_quote;
	
	single_quote = false;
	double_quote = false;
	input = data->input;
	while (*input)
	{
		if ((*input == '\"') && (single_quote == false))
			double_quote = !double_quote;
		else if ((*input == '\'') && (double_quote == false))
			single_quote = !single_quote;
		input++;
	}
	if (single_quote || double_quote)
	{
		printf("une quote n'est pas ferme\n");
		exit(0);
	}
}


void	parsing(t_data	*data)
{
	check_quote_error(data);
	replace_var_env(data);
	//TODO creat all tokens form the output user
	// check readme parsing
	//add_token(&data->token, "ls", 6);
}
