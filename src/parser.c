/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:40:00 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/26 01:24:39 by leothoma         ###   ########.fr       */
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

int	check_for_redirs(int type)
{
	if (type == 1 || type == 2 || type == 3 || type == 4)
		return (1);
	return (0);
}

int	check_for_cmds(int type)
{
	if (type == 6 || type == 7)
		 return (1);
	return (0);
}

void	add_redir_list(t_token *token, t_redir **redir_list)
{
	t_redir	*new;
	t_redir *tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->target = token->next->str;
	new->type = token->type;
	new->next = NULL;
	if (!*redir_list)
		*redir_list = new;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
void	add_cmd_list(t_token *token, t_redir **redir_list)
{
	t_redir	*new;
	t_redir *tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	new->target = token->next->str;
	new->type = token->type;
	new->next = NULL;
	if (!*redir_list)
		*redir_list = new;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	save_redir_info(t_token *token, t_cmd *cmd_list)
{
	add_redir_list(token, &cmd_list->redirs);
}

int	get_n_command(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 6 || token->type == 7)
			i++;
		token = token->next;
	}
	return (i);
}

void	save_cmds_info(t_token *token, t_cmd *cmd_list)
{
	int	n_command;
	int	i;

	i = 0;
	n_command = get_n_command(token);
	cmd_list->cmd = malloc(sizeof(char *) * n_command + 1);
	while (token && token->type != PIPE)
	{
		if (token->type == 6 || token->type == 7)
		{
			cmd_list->cmd[i] = ft_strdup(token->str);
			i++;
		}
		token = token->next;
	}
	cmd_list->cmd[i] = 0;
}


void	extract_redirs(t_token *token, t_cmd *cmd_list)
{
	while (token && token->type != PIPE)
	{
		if (check_for_redirs(token->type))
			save_redir_info(token, cmd_list);
		token = token->next;	
	}
}

void	extract_cmds(t_token *token, t_cmd *cmd_list)
{
	while (token && token->type != PIPE)
	{
		if (check_for_cmds(token->type))
			save_cmds_info(token, cmd_list);
		token = token->next;	
	}
}

void	advance_pointer(t_token **token)
{
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	if ((*token)->next)
		(*token) = (*token)->next;
}

void	parser(t_data *data, t_cmd *cmd_list)
{
	t_values	*vals;	
	// save_redir_info(data->token, cmd_list);
	extract_redirs(data->token, cmd_list);
	save_cmds_info(data->token, cmd_list);
	advance_pointer(&data->token);
	// extract_cmds(data->token, cmd_list);
	//advance_pointer(&data->token);
		// int	i = 0;

		// while (cmd_list->redirs)
		// {
		// 	printf("%s\n", cmd_list->redirs->target);
		// 	cmd_list->redirs = cmd_list->redirs->next;
		// }



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
