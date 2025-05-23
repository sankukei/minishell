/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:03:53 by leothoma          #+#    #+#             */
/*   Updated: 2025/05/16 11:53:22 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum s_type
{
	HEREDOC = 1,  // <<
	APPEND, // >>
	INPUT, // <
	TRUNC, // >
	PIPE, // |
	CMD,
	ARG,
}	t_type;

typedef enum s_boolen
{
	false,
	true,
}	t_boolen;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}   t_token;

typedef struct s_data
{
	char 			*input;
	t_boolen		single_quote;
	t_boolen		double_quote;
	t_token			*token;
	char			**env;
	int test;
}   t_data;

