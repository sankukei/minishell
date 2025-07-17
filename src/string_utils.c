/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:05:03 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/13 03:05:04 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_iscapitalise(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	get_n_command_new(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds->cmd)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	align_pointer(t_token **token)
{
	while (token && *token && ((*token)->type == 6 || (*token)->type == 7))
		*token = (*token)->next;
}
