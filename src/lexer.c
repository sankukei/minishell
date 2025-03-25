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

int	check_token_type(t_data *data, char *str)
{
	int	len;
	t_token *token;
	
	len = ft_strlen(str);
	token = data->token;
	if (!ft_memcmp(str, INPUT_REDIR_STR, len))
		return (1);
	else if (!ft_memcmp(str, HEREDOC_STR, len))
		return (2);
	else if (!ft_memcmp(str, REDIR_STR, len))
		return (3);
	else if (!ft_memcmp(str, APPEND_STR, len))
		return (4);
	else if (!ft_memcmp(str, PIPES_STR, len))
		return (5);
	else
		return (7);
	// missing CMD / ARGS for type 6
	// CMD -> parse $PATH and check for implemenbted builtins
}

/*void	init_token_types(t_data *data, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		check_token_types(data, tokens[i]);
		i++;
	}
}*/

int	is_spaces(char c)
{
	return (c == 32 || (c > 8 && c < 14) || c == 0);
}

void	check_quotes(char c, t_data *data)
{
	if (c == '\"' && data->single_quote == false)
		data->double_quote = !(data->double_quote);
	else if (c == '\'' && data->double_quote == false)
		data->single_quote = !(data->single_quote);
}

int	get_world_len(char **str, t_data *data)
{
	int	len;

	len = 0;
	check_quotes(**str, data);
	data->test = 0;
	if ((*str)[0] == '\"' || (*str)[0] == '\'')
		len++;
	while (is_spaces(**str))
		*str += 1;
	while ((!is_spaces((*str)[len]) && **str) || data->double_quote || data->single_quote)
	{
		check_quotes((*str)[len], data);
		len++;
	}
	return (len);
}

void	lexer(t_data *data, char *str)
{
	char	*buffer;
	int	type;
	int	len;

	len = 0;
	while (*str)
	{
		len = get_world_len(&str, data);		
		if (0 == len)
			return ; // A REVOIR
		buffer = malloc(len * sizeof(char) + 1);
		memset(buffer, '\0', len);
		ft_strlcpy(buffer, str, len + 1);
		type = check_token_type(data, buffer);
		add_token(&data->token, buffer, type);
		free(buffer);
		str += len;
	}
	t_token *token = data->token;
	while (token)
	{
		printf("STRING : %s -> TYPE : %d\n", token->str, token->type);
		token = token->next;
	}
}
