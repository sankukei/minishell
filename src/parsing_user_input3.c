/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:01:17 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/18 12:13:08 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
			token = get_operator_token(data->input, &i);
		else
			token = extract_token(data->input, &i);
		if (token && *token)
			add_token_refacto(&list, token);
		else
			free(token);
	}
	data->token = list;
}

char	*remove_quote(char *str)
{
	int				i;
	int				l;
	unsigned char	c;
	char			*dest;

	dest = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				dest[l++] = str[i++];
			i++;
		}
		else
			dest[l++] = str[i++];
		dest[l] = 0;
	}
	free(str);
	return (dest);
}

void	extern_quote_handler(t_data *data)
{
	t_token	*token;
	char	*str;

	token = data->token;
	while (token)
	{
		str = token->str;
		token->str = remove_quote(str);
		token = token->next;
	}
}
