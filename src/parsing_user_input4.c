/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_user_input4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:01:20 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 06:47:56 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	affiche_token_test(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		printf("token numero %d: %s\ntype : %d\n", i++,
			token->str, token->type);
		token = token->next;
	}
}

void	put_hard_coded_type(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->str[0] == '|' && token->str[1] == '\0')
			token->type = PIPE;
		if (token->str[0] == '<' && token->str[1] == '\0')
			token->type = INPUT;
		if (token->str[0] == '>' && token->str[1] == '\0')
			token->type = TRUNC;
		if (token->str[0] == '<' && token->str[1] == '<'
			&& token->str[2] == '\0')
			token->type = HEREDOC;
		if (token->str[0] == '>' && token->str[1] == '>'
			&& token->str[2] == '\0')
			token->type = APPEND;
		token = token->next;
	}
}

void	classify_cmd_and_args(t_token *token)
{
	t_boolen	expect_cmd;
	t_type		prev_type;

	expect_cmd = true;
	prev_type = -1;
	while (token)
	{
		if (prev_type == INPUT)
			token->type = FD;
		if (token->type == -1)
		{
			if (expect_cmd)
			{
				token->type = CMD;
				expect_cmd = false;
			}
			else if (prev_type >= HEREDOC && prev_type <= TRUNC)
				token->type = 8;
			else
				token->type = ARG;
		}
		if (token->type == PIPE)
			expect_cmd = true;
		prev_type = token->type;
		token = token->next;
	}
}

void	type_tokens(t_data *data)
{
	put_hard_coded_type(data);
	classify_cmd_and_args(data->token);
}

int	check_pipe_rule(t_token *previous, t_token *current)
{
	if (previous == NULL || !current->next)
		return (printf("Syntax error: unexpected token '|'\n"), 1);
	if (current->next->type == PIPE || current->next->type == TRUNC || current->next->type == APPEND)
		return (printf("Syntax error: unexpected token '|'\n"), 1);
	return (0);
}

int	is_redir_token(t_token *current)
{
	return (current->type >= 1 && current->type <= 4);
}

int	check_infile_rule(t_token *previous, t_token *current)
{
	int	i;

	i = 0;
	current = current->next;
	if  (previous && previous->type == CMD)
		i++;
	while (current && current->type != PIPE && !is_redir_token(current))
	{
		if (current->type == CMD)
			i++;
		else if (current->type == FD)
			i++;
		current = current->next;
	}
	if (i < 2)
		return (printf("Syntax error: unexpected token '<'\n"));
	return (0);
}

int	check_outfile_rule(t_token *previous, t_token *current)
{
	int	i;
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
		if (current->type == TRUNC || current->type == APPEND || current->type == HEREDOC)
		{
			if (check_syntax(TRUNC, previous, current))
				return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

