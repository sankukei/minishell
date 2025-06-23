/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:40:00 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/22 17:40:01 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**fill_cmds(t_token *token)
{
	char	**res;

	while (token)
	{
		if (token->type == PIPE)
		{
			//add_node;
		}
		token = token->next;
	}
	res = 0;
	return (res);
}

void	extract_based_on_types(char *token_name, int token_type)
{
//	if (token_type == HEREDOC)
//		ft_strdup(cmd_list->heredoc, );
//	else if (token_type == APPEND)

}

void	extract_values(t_token *token, t_cmd *cmd_list)
{
	while (token)
	{
	//	extract_based_on_types(token->str, token->type, cmd_list);
		
	}
}

void	extract_redirs(t_token *token)
{
	while (token)
	{
		;
	}
}

void	parser(t_data *data, t_cmd *cmd_list)
{
	t_values	*vals;
	
	//split_tokens_into_pipelines(data);
	extract_redirs(data->token);
//	extract_cmds(data->token, cmd_list);

	cmd_list->cmd = fill_cmds(data->token);
}

/* parser -> *data & des commandes pipeline
 *	traite chaque cmd et les assemble pour donner facilement a l'exec
 *
 *	return value: char** (cmd+arg)
 *		      une struc qui reprensente toutes les redirection si il y en a
 *		      les path (a voir)
 *		      TOUT ca dans une structure qui contient tout ces types
 *
 *
 *
 *
 *
 * */

/*
int	fill_args(char **res, t_token **token, int *is_reddir, t_exec *vars)
{
	int	i;

	if (vars->is_heredoc)
		return (fill_args_for_heredoc(res, token, is_reddir));
	i = 0;
	while (*token && (*token)->type != PIPE && (*token)->type != HEREDOC)
	{
		if ((*token)->type == APPEND || (*token)->type == INPUT || (*token)->type == TRUNC)
		{
			*is_reddir = 1;
			break ;
		}
		res[i] = ft_strdup((*token)->str);
		if (!res[i])
			return (-1);
		*token = (*token)->next;
		i++;
	}
	res[i] = NULL;
	return (i);
} */
