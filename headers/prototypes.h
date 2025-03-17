/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:56 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/17 17:02:59 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// main
void		minishell_launcher(t_data *data);

// start parsing
void		parsing(t_data	*data);

// parsing input
void		check_quote_error(t_data *data);
void		var_env_handler(t_data *data);
char		*detect_var_env(char *input);

// parsing tokinsation
void		init_token_rules(t_data *data);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);

// string_utils
int     ft_iscapitalise(char c);

