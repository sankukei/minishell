/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:40:00 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 07:11:31 by amedenec         ###   ########.fr       */
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

int	check_for_redirs(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == 1 || token->type == 2 || token->type == 3 || token->type == 4)
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
	t_redir *tmp;
	
	new = calloc(1, sizeof(t_redir)); 
	//new = malloc(sizeof(t_redir));
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
		printf("ALED\n");
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
		if (token->type == 1 || token->type == 2 || token->type == 3 || token->type == 4)
			add_redir_list(token, redir_list);
		token = token->next;
	}
}

// CHECK LE RETURN POUR LE MALLOC FAIL
char	**save_cmds_info(t_token *token, t_cmd *cmd_list)
{
	int	n_count;
	int	i;

	i = 0;
	n_count = get_malloc_size_for_cmds(token);
	cmd_list->cmd = malloc(sizeof(char *) * (n_count + 2));
	if (!cmd_list->cmd)
		return (1);
	bzero(cmd_list->cmd, sizeof(char *) * (n_count + 2));
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
	return (cmd_list->cmd);
}

void	add_cmd_list(t_token *token, t_cmd **cmd_list)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	bzero(new, sizeof(t_cmd));
	new->cmd = save_cmds_info(token, *cmd_list);
	if (check_for_redirs(token))
		get_reddirs(token, &(*cmd_list)->redirs);
	new->next = NULL;
	if (!*cmd_list)
		*cmd_list = new;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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

void	extract_redirs(t_token *token, t_cmd *cmd_list)
{
	while (token && token->type != PIPE)
	{
	//	if (check_for_redirs(token->type))
	//		save_redir_info(token, cmd_list);
	//	token = token->next;	
	}
}

void	extract_cmds(t_token *token, t_cmd *cmd_list)
{
	if (check_for_cmds(token->type))
		add_cmd_list(token, &cmd_list);
}

void	advance_pointer(t_token **token)
{
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	if ((*token) && (*token)->next)
		(*token) = (*token)->next;
}

void	parser(t_data *data, t_cmd **cmd_list)
{
	t_values	*vals;	
	
	while (data->token)
	{
		add_cmd_list(data->token, cmd_list);
		advance_pointer(&data->token);
	}
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
