/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:19:29 by leothoma          #+#    #+#             */
/*   Updated: 2025/06/30 01:07:04 by amedenec         ###   ########.fr       */
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
	while (token && *token && ((*token)->type == 1 || (*token)->type == 6 || (*token)->type == 7))
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
	bzero(res, (count + 1) * sizeof(char *));
	return (res);
}

// int	fill_args_for_heredoc(char **res, t_token **token, int *is_reddir)
// {
// 	int	i;

// 	i = 0;
// 	while (*token && (*token)->type != PIPE)
// 	{
// 		if ((*token)->type == APPEND || (*token)->type == INPUT || (*token)->type == TRUNC)
// 		{
// 			*is_reddir = 1;
// 			break ;
// 		}
// 		*token = (*token)->next;
// 		i++;
// 	}
// 	return (i);
// }

// int	fill_args(char **res, t_token **token, int *is_reddir, t_exec *vars)
// {
// 	int	i;

// 	if (vars->is_heredoc)
// 		return (fill_args_for_heredoc(res, token, is_reddir));
// 	i = 0;
// 	while (*token && (*token)->type != PIPE && (*token)->type != HEREDOC)
// 	{
// 		if ((*token)->type == APPEND || (*token)->type == INPUT || (*token)->type == TRUNC)
// 		{
// 			*is_reddir = 1;
// 			break ;
// 		}
// 		res[i] = ft_strdup((*token)->str);
// 		if (!res[i])
// 			return (-1);
// 		*token = (*token)->next;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (i);
// }


