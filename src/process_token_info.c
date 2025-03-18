/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:55:13 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/18 14:55:14 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_rules(int	type, int next)
{
	if (type == 1 && next != FD)
		return (1);
	else if (type == 2 && next != ARGS)
		return (1);
	else if (type == 3 && next != FD)
		return (1);
	else if (type == 4 && next != FD)
		return (1);
	else if (type == 5 && next != CMD)
		return (1);
	else if (type == 6 && (next != ARGS || next != PIPES || next != REDIR))
		return (1);
	else if (type == 7 && (next != ARGS || next != PIPES))
		return (1);
	return (0);
}

int	process(t_token *token)
{
	// check le type du premier token et verifier que cmd ou redirr
	while (token && token->next)
	{
		if (!(check_rules(token->type, token->next->type)))
			return (0);
		token = token->next;
	}
	return (1);
}

/* 
 * echo "hello" >> text.txt
 *  6	   7	4     7
 * types => {
 * 	1 = INPUT (<);
 * 	2 = HEREDOC (<<);
 * 	3 = TRUNC (>);
 * 	4 = APPEND (>>);
 * 	5 = PIPES (|);
 * 	6 = CMD (ex: 'ls'); // a verifier que cest uniquement dans le path / builtin
 * 	7 = ARG (ex: ls '-l');
 * }

	1 = [
		"FD"
	]
	2 = [
		"ARGS"
	]
	3 = [
		"FD"
	]
	4 = [
		"FD"
	]
	5 = [
		"CMD",
	]
	6 = [
		"ARGS",
		"PIPES",
		"REDIR[>, >>]"

	]
	7 = [
		"PIPES",
		"REDIR[>, >>]",
	]

	minishell> : [CMD / REDIRECTION] [ARG] ...

*/
