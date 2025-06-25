/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:18:00 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/05 03:32:10 by amedenec         ###   ########.fr       */
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
	while (str[i])
		free(str[i++]);
	free(str);
}

void	clear_redir_struct(t_redir **redirs)
{
	t_redir	*temp;

	while (redirs && *redirs)
	{
		if ((*redirs)->next)
			temp = (*redirs)->next;
		free((*redirs)->target);
		free(*redirs);
		if ((*redirs)->next)
			*redirs = temp;
	}
}

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*temp;

	while (cmds && *cmds)
	{
		temp = (*cmds)->next;
		clear_array((*cmds)->cmd);
		//clear_array((*cmds)->path); a mettre si on use le path 
		if (&(*cmds)->redirs)
			clear_redir_struct(&(*cmds)->redirs);
		free(*cmds);
		if (&(*cmds)->next)
			*cmds = temp;
	}
}

void	prepare_next_input(t_data *data, t_cmd **cmds)
{
	if (data->input)
		free(data->input);
	if (&data->front_token)
		clear_struct(&data->front_token);
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
