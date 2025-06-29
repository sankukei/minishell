/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:18:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/27 07:18:57 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	clear_struct(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->str);
		free(*tokens);
		*tokens = tmp;
	}
}

void	clear_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	clear_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	clear_redir_struct(t_redir **redirs)
{
	t_redir *tmp;
	
	while (*redirs)
	{
		tmp = (*redirs)->next;
		free((*redirs)->target);
		free(*redirs);
		*redirs = tmp;
	}
}

void	clear_cmd_node(t_cmd *cmds)
{
	if (!cmds)
		return ;
	clear_array(cmds->cmd);
	clear_redir_struct(&cmds->redirs);
	//rajouter path si on use;
	free(cmds);
}

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*temp;

	if (!cmds || !*cmds)
		return ;

	while (*cmds)
	{
		temp = (*cmds)->next;
		//clear_redir_struct(&temp->redirs);
		//clear_redir_struct(&(*cmds)->redirs);
		clear_cmd_node(*cmds);
		*cmds = temp;
	}
}

void	prepare_next_input(t_data *data, t_cmd **cmds)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
//	printf("[%s]\n", data->front_token->str);
//	printf("[%s]\n", data->front_token->next->str);
//	printf("[%s]\n", data->front_token->next->next->str);
//	if (&data->front_token)
//		clear_struct(&data->front_token);
	if (cmds && *cmds)
	{
		clear_cmds(cmds);
		*cmds = NULL;
	}
}

void	exit_program(t_data *data)
{
	free(data->input);
	clear_struct(&data->front_token);
	clear_double_array(data->env);
	clear_cmds(&data->cmd);
	free(data);
	exit(1);
}
