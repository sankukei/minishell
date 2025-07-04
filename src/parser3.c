/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:07:50 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 20:09:12 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_for_redirs(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == 1 || token->type == 2
			|| token->type == 3 || token->type == 4)
			return (1);
		token = token->next;
	}
	return (0);
}

int	check_for_cmds(int type)
{
	if (type == 6 || type == 7)
		return (1);
	return (0);
}

int	get_malloc_size_for_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == 6 || token->type == 7)
			i++;
		token = token->next;
	}
	return (i);
}

void	add_redir_list(t_token *token, t_redir **redir_list)
{
	t_redir	*new;
	t_redir	*tmp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return ;
	new->target = token->next->str;
	new->type = token->type;
	new->next = NULL;
	if (!*redir_list)
	{
		*redir_list = new;
	}
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	get_reddirs(t_token *token, t_redir **redir_list)
{
	while (token && token->type != PIPE)
	{
		if (token->type == 1 || token->type == 2
			|| token->type == 3 || token->type == 4)
			add_redir_list(token, redir_list);
		token = token->next;
	}
}
