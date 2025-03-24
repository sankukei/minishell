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
	t_token *token;
	
	token = data->token;
	if (!ft_memcmp(str, INPUT_REDIR_STR, ft_strlen(str)))
	{
		return (1);
		printf(" REDIR ", data->token->type);
	}
	else if (!ft_memcmp(str, HEREDOC_STR, ft_strlen(str)))
	{
		printf(" HEREDOC ");
		return (2);
	}
	else if (!ft_memcmp(str, REDIR_STR, ft_strlen(str)))
	{
		printf(" REDIR ");
		return (3);
	}
	else if (!ft_memcmp(str, APPEND_STR, ft_strlen(str)))
	{
		printf(" APPEND ");
		return (4);
	}	
	else if (!ft_memcmp(str, PIPES_STR, ft_strlen(str)))
	{
		printf(" PIPES ");
		return (5);
	}		
	return (0);
	// missing CMD / ARGS
	// CMD -> parse $PATH and check for implemenbted builtins
	// the rest is all ARGS
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
	return (c == 32 || (c > 8 && c < 12));
}

//void	handle_quotes(t_data **data, char c)
//{
	
//}

/*void	check_quotes(char c, t_data *data)
{

	if ((c == '\"') && (data->single_quote == false))
		data->double_quote = !(data->double_quote);
	else if (c == '\'') && (data->double_quote == false))
		data->single_quote = !(data->single_quote);

	return (0);
}*/

int	get_world_len(char *str, t_data *data)
{
	int	len;

	len = 0;
	if ((str[len] == '\"') && (data->single_quote == false))
		data->double_quote = !(data->double_quote);
	else if ((str[len] == '\'') && (data->double_quote == false))
		data->single_quote = !(data->single_quote);
	if (str[0] == '\"' || str[0] == '\'')
		len++;
	while ((!is_spaces(str[len]) && str[len]) || data->double_quote || data->single_quote)
	{
		if ((str[len] == '\"') && (data->single_quote == false))
			data->double_quote = !(data->double_quote);
		else if ((str[len] == '\'') && (data->double_quote == false))
			data->single_quote = !(data->single_quote);
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
		len = get_world_len(str, data);		
		if (0 == len)
			return ; // A REVOIR
		buffer = malloc(len * sizeof(char) + 1);
		memset(buffer, '\0', len);
		ft_strlcpy(buffer, str, len + 1);
		type = check_token_type(data, buffer);
		add_token(&data->token, buffer, type);
		free(buffer);
		str += len + 1;
	}
	t_token *token = data->token;
	while (token)
	{
		printf("%s\n", token->str);
		printf("%s\n", token->str);
		token = token->next;
	}
	// while (data->token)
	// {
	// 	printf("%s", data->token->str);
	// 	data->token = data->token->next;
	// }
	//print_list(&data, "TOKEN");
}
