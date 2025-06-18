/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <sankukei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:19:29 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/14 05:34:38 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	skip_first_tokens(t_token **token)
{
	int	count;

	count = 0;
	while (token && *token && ((*token)->type == 6 || (*token)->type == 7))
	{
		count++;
		*token = (*token)->next;
	}
	return (count);
}

char	**alloc_args_array(int count)
{
	char	**res;

	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (res);
}

int	fill_args(char **res, t_token **token, int *is_reddir)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != 5)
	{
		if ((*token)->type == 1 || (*token)->type == 2 || (*token)->type == 3 || (*token)->type == 4)
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
}
