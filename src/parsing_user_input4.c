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

static void	update_token(t_type *prev_type, t_token **token)
{
	*prev_type = (*token)->type;
	*token = (*token)->next;
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
		update_token(&prev_type, &token);
	}
}

int	check_pipe_rule(t_token *previous, t_token *current)
{
	if (previous == NULL || !current->next)
		return (printf("Syntax error: unexpected token '|'\n"), 1);
	if (current->next->type == PIPE || current->next->type == TRUNC
		|| current->next->type == APPEND)
		return (printf("Syntax error: unexpected token '|'\n"), 1);
	return (0);
}
