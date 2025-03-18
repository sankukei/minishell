/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:40:10 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/18 15:40:10 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	check_token_types(t_data *data, char *str)
{
	t_token *token;
	
	token = data->token;
	if (ft_memcmp(str, INPUT_REDIR_STR, ft_strlen(str)))
		add_token(&token, str, 1);
	else if (ft_memcmp(str, HEREDOC_STR, ft_strlen(str)))
		add_token(&token, str, 2);
	else if (ft_memcmp(str, REDIR_STR, ft_strlen(str)))
		add_token(&token, str, 3);
	else if (ft_memcmp(str, APPEND_STR, ft_strlen(str)))
		add_token(&token, str, 4);
	else if (ft_memcmp(str, PIPES_STR, ft_strlen(str)))
		add_token(&token, str, 5);
	// missing CMD / ARGS
	// CMD -> parse $PATH and check for implemenbted builtins
	// the rest is all ARGS
}

void	init_token_types(t_data *data, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		check_token_types(data, tokens[i]);
		i++;
	}
}

void	split_tokens(t_data *data)
{
	char	**tokens;

	tokens = ft_split(data->input, ' ');
	init_token_types(data, tokens);
	while (data->token)
	{
		printf("%s", data->token->str);
		data->token = data->token->next;
	}
}
