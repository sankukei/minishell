/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:08:46 by leothoma          #+#    #+#             */
/*   Updated: 2025/07/03 20:18:43 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**save_cmds_info(t_token *token, t_cmd *cmd_list)
{
	int		n_count;
	int		i;
	char	**cmd_array;

	(void)cmd_list;
	i = 0;
	n_count = get_malloc_size_for_cmds(token);
	cmd_array = malloc(sizeof(char *) * (n_count + 1));
	if (!cmd_array)
		return (0);
	ft_bzero(cmd_array, sizeof(char *) * (n_count + 1));
	while (token && token->type != PIPE)
	{
		if (token->type == 6 || token->type == 7)
		{
			cmd_array[i] = ft_strdup(token->str);
			if (!cmd_array[i])
				return (0);
			i++;
		}
		token = token->next;
	}
	cmd_array[i] = 0;
	return (cmd_array);
}

static void	free_add_cmd_list(t_cmd *new, t_data *data)
{
	free(new);
	clear_cmds(&data->cmd);
}

int	add_cmd_list(t_data *data, t_token *token, t_cmd **cmd_list)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	ft_bzero(new, sizeof(t_cmd));
	new->cmd = save_cmds_info(token, *cmd_list);
	if (!new->cmd)
		return (free_add_cmd_list(new, data), 0);
	if (check_for_redirs(token))
		get_reddirs(token, &new->redirs);
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
	data->n_commands += 1;
	return (1);
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

void	advance_pointer(t_token **token)
{
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	if ((*token) && (*token)->next)
		(*token) = (*token)->next;
}
