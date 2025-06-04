/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:58:02 by amedenec          #+#    #+#             */
/*   Updated: 2025/06/05 00:01:33 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int get_len_of_double_char(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    **dup_envp(char **envp)
{
    char    **dest;
    char    *tmp;
    int     i;
    int     len;
    
    i = 0;
    len = get_len_of_double_char(envp);
    dest = malloc(sizeof(char *) * (len + 1));
    while (envp[i])
    {
        tmp = ft_strdup(envp[i]);
        dest[i] = tmp;
        i++;
    }
    dest[i] = NULL;
    return (dest);
}


void    init(t_data *data, char **envp)
{
    data->last_exit_status = 0;
    data->token = NULL;
	data->single_quote = false;
	data->double_quote = false;
	data->front_token = NULL;
    data->env = dup_envp(envp);

}