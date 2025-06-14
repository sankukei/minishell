/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:53:10 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/14 05:27:43 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_token	*find_last_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token && token->next)
		token = token->next;
	return (token);
}

void	print_list(t_data **data, char const *option)
{
	t_token	*current;
	int		i;

	(void)option;
	i = 0;
	current = (*data)->token;
	while (current)
	{
		printf("index : %d\n", i++);
		printf("string-> %s\n", current->str);
		current = current->next;
	}
}

t_token	*find_penultimate_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token && token->next && token->next->next)
		token = token->next;
	return (token);
}

int	count_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token && token->next)
	{
		token = token->next;
		i++;
	}
	return (i + 1);
}

int	add_token(t_token **token, char *str, int type)
{
	t_token	*new_token;
	t_token	*last_token;

	if (token == NULL)
		return (1);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (1);
	new_token->next = NULL;
	new_token->str = ft_strdup(str);
	new_token->type = type;
	if (*token == NULL)
		*token = new_token;
	else
	{
		last_token = find_last_token(*token);
		last_token->next = new_token;
	}
	return (0);
}
