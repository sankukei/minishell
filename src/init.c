/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:58:02 by amedenec          #+#    #+#             */
/*   Updated: 2025/05/06 03:21:16 by adam             ###   ########.fr       */
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
    data->token = NULL;
	data->single_quote = false;
	data->double_quote = false;
    data->env = dup_envp(envp); // malloc l'envp

    //int i;
    //i = 0;
    //while (data->env[i])
    //   printf("%s\n", data->env[i++]);
}