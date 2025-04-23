/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:56 by leothoma          #+#    #+#             */
/*   Updated: 2025/03/26 06:16:44 by amedenec         ###   ########.fr       */
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
void		init_token_types(t_data *data, char **tokens);
void		check_token_types(t_data *data, char *str);
void		split_tokens(t_data *data);

// struct_utils
t_token		*find_last_token(t_token *token);
t_token		*find_penultimate_token(t_token *token);
int			count_token(t_token *token);
int			add_token(t_token **token, char *str, int type);
void		print_list(t_data **data, char const *option);

// setup_signals
void	handle_sigint(int signum);
void	setup_signals(void);


// string_utils
int     ft_iscapitalise(char c);

// lexer
void	lexer(t_data *data, char *str);

// clear_utils
void	prepare_next_input(t_data *data);
void	clear_struct(t_token **tokens);
void	exit_program(t_data *data);

// EXEC
int	__EXEC_STARTUP__(t_token *token);
