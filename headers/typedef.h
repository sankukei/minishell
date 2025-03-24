/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:03:53 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/17 17:07:51 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum s_boolen
{
	false,
	true,
}	t_boolen;

typedef struct s_token
{
	char			*str;
	int				type;
	char			*rules;
	struct s_token	*next;
}   t_token;

typedef struct s_data
{
	char 			*input;
	t_boolen		single_quote;
	t_boolen		double_quote;
	t_token			*token;
}   t_data;

