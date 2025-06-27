/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_list_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:27:18 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/27 06:46:28 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	add_token_refacto(t_token **list, char *str)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	bzero(new, sizeof(new));
	new->str = str;
	new->type = -1;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
