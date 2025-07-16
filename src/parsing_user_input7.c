/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:20:59 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/16 14:20:59 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_redir_token(t_token *current)
{
	return (current->type >= 1 && current->type <= 4);
}

int	check_infile_rule(t_token *previous, t_token *current)
{
	int	i;

	i = 0;
	current = current->next;
//	if (previous && previous->type == CMD)
//		i++;
	while (current && current->type != PIPE && !is_redir_token(current))
	{
	//	if (current->type == CMD)
	//		i++;
		if (current->type == FD)
			i++;
		current = current->next;
	}
	if (i < 1)
		return (printf("Syntax error: unexpected token '<'\n"));
	return (0);
}

int	check_outfile_rule(t_token *previous, t_token *current)
{
	int		i;
	char	str[3];

	ft_bzero(str, 3);
	i = 0;
	ft_strlcpy(str, current->str, ft_strlen(current->str) + 1);
	current = current->next;
	while (current && current->type != PIPE && !is_redir_token(current))
	{
		if (current->type == FD)
			i++;
		current = current->next;
	}
	if (i != 1)
		return (printf("Syntax error: unexpected token '%s'\n", str));
	return (0);
}

int	check_syntax(int type, t_token *previous, t_token *current)
{
	if (type == PIPE)
		if (check_pipe_rule(previous, current))
			return (1);
	if (type == INPUT)
		if (check_infile_rule(previous, current))
			return (1);
	if (type == TRUNC)
		if (check_outfile_rule(previous, current))
			return (1);
	return (0);
}

int	check_token_syntax(t_token *head)
{
	t_token	*current;
	t_token	*previous;

	if (!head)
		return (1);
	current = head;
	previous = NULL;
	while (current)
	{
		if (current->type == PIPE)
			if (check_syntax(PIPE, previous, current))
				return (1);
		if (current->type == INPUT)
			if (check_syntax(INPUT, previous, current))
				return (1);
		if (current->type == TRUNC || current->type == APPEND
			|| current->type == HEREDOC)
		{
			if (check_syntax(TRUNC, previous, current))
				return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}
