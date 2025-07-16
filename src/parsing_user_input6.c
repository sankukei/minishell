/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:06:14 by amedenec          #+#    #+#             */
/*   Updated: 2025/07/16 23:01:32 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	skip_quote(char *str, int i)
{
	char		quote;
	int			len;

	quote = str[i++];
	len = 0;
	while (str[i] && str[i] != quote)
	{
		i++;
		len++;
	}
	return (len + 2);
}

char	*extract_token(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] && !is_operator(str[*i]) && !is_space(str[*i]))
	{
		if (str[*i] == '\"' || str[*i] == '\'')
			*i += skip_quote(str, *i);
		else
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}


static char	*extract_operator(char *input, int *i)
{
	char	*token;

	if ((input[*i] == '<' || input[*i] == '>')
		&& input[*i] == input[*i + 1])
	{
		token = ft_substr(input, *i, 2);
		*i += 2;
	}
	else
	{
		token = ft_substr(input, *i, 1);
		(*i)++;
	}
	return (token);
}

void	tokenisation(t_data *data)
{
	int		i;
	char	*token;
	t_token	*list;

	list = NULL;
	i = 0;
	while (data->input[i])
	{
		while (is_space(data->input[i]))
			i++;
		if (is_operator(data->input[i]))
			token = extract_operator(data->input, &i);
		else
			token = extract_token(data->input, &i);
		if (token && *token)
			add_token_refacto(&list, token);
		else
			free(token);
	}
	data->token = list;
}

char	*get_operator_token(char *input, int *i)
{
	if ((input[*i] == '<' || input[*i] == '>')
		&& input[*i] == input[*i + 1])
	{
		*i += 2;
		return (ft_substr(input, *i - 2, 2));
	}
	else
	{
		(*i)++;
		return (ft_substr(input, *i - 1, 1));
	}
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
