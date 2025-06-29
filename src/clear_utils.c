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
			free(str[i++]);
		free(str);
	}
}

void	clear_redir_struct(t_redir **redirs)
{
	t_redir *tmp;
	
	while (*redirs)
	{
		printf("xd\n");
		tmp = (*redirs)->next;
		free((*redirs)->target);
		free(*redirs);
		*redirs = tmp;
	}
}

void	clear_cmd_node(t_cmd **cmds)
{
	clear_array((*cmds)->cmd);
	free(*cmds);
	//rajouter path si on use;
}

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*temp;

	//temp = *cmds;
	while (temp)
	{
		temp = (*cmds)->next;
		write(1, "zaza\n", 5);
		//clear_redir_struct(&temp->redirs);
		clear_redir_struct(&(*cmds)->redirs);
		write(1, "zaza\n", 5);
		clear_cmd_node(cmds);
		write(1, "zaza\n", 5);
		if (temp)
			temp = temp->next;
		write(1, "zaza\n", 5);
	}
}

void	prepare_next_input(t_data *data, t_cmd **cmds)
{
	if (data->input)
		free(data->input);
//	printf("[%s]\n", data->front_token->str);
//	printf("[%s]\n", data->front_token->next->str);
//	printf("[%s]\n", data->front_token->next->next->str);
//	if (&data->front_token)
//		clear_struct(&data->front_token);
	if (cmds)
		clear_cmds(cmds);
}

void	exit_program(t_data *data)
{
	free(data->input);
	clear_struct(&data->front_token);
	clear_double_array(data->env);
	free(data);
	exit(1);
}
